#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addvdialog.h"
#include "addadialog.h"
#include "stdio.h"
#include <iostream>
#include "asio.hpp"
#include "ostream"
#include "edittrialdialog.h"
#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>
#include <QKeySequence>


using namespace std;
using asio::ip::tcp;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->trialorderBox->addItem("random_with_replacement","random_with_replacement");
    ui->trialorderBox->addItem("random_without_replacement","random_without_replacement");
    ui->trialorderBox->addItem("sequential","sequential");

    ui->trialListWidget->setDragDropMode(QAbstractItemView::InternalMove); // define the drag-and-drop mode for modify the trials order in trialListWidget
    connect(ui->trialListWidget->model(), &QAbstractItemModel::rowsMoved, this, &MainWindow::updateTrialOrder);

    // shortcut per il tasto Canc sulla list widget
    QShortcut* deleteShortcut = new QShortcut(QKeySequence::Delete, ui->trialListWidget);
    connect(deleteShortcut, &QShortcut::activated,
            this, &MainWindow::on_trialdeleteButton_clicked);

    refreshDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshDisplay()
{
    saveExpData();
    // 2) Pulisci la lista e l'edit JSON sperimentale
    ui->trialListWidget->clear();
    ui->experimentaljsonEdit->clear();

    // 3) Assicura che trialFileNames abbia almeno la stessa dimensione di exp.trials
    if (trialFileNames.size() < static_cast<int>(exp.trials.size())) {
        trialFileNames.resize(exp.trials.size());
    }

    // 4) Ricostruisci gli item nella stessa sequenza di exp.trials
    for (int i = 0; i < static_cast<int>(exp.trials.size()); ++i) {
        const auto& t = exp.trials[i];

        // Crea il nuovo item e ne imposti il testo
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(t.name));

        // Se esiste un percorso file salvato per questo trial, lo ripristiniamo
        const QString& savedPath = trialFileNames[i];
        if (!savedPath.isEmpty()) {
            item->setData(Qt::UserRole, savedPath);
        }

        // Aggiungi l'item alla list widget
        ui->trialListWidget->addItem(item);
    }

    // 5) Mostra il JSON complessivo dell'esperimento
    QString fullJson = QString::fromStdString(exp.toJSON());
    ui->experimentaljsonEdit->appendPlainText(fullJson);

    // 6) Riposiziona il focus sul pulsante Connect (come prima)
    ui->connectButton->setFocus();
}

void MainWindow::saveExpData()
{
    exp.subjectname = ui->subjectnameEdit->text().toStdString();
    exp.numberofloops = ui->numloopSpinBox->value();
    exp.writeoutput = ui->writeoutputBox->isChecked();
    exp.trialordering = ui->trialorderBox->currentText().toStdString();
}

string MainWindow::getCombinedTrialJSON(list<int>& trialstomix)
{
    if(trialstomix.size()==0) return "{}";
    TrialStub base;
    auto ttmit = trialstomix.begin();
    auto bit = exp.trials.begin();
    advance(bit,*ttmit);
    base.fromJSON((*bit).toJSON());
    ttmit++;
    while(ttmit!=trialstomix.end()){
        bit = exp.trials.begin();
        advance(bit,*ttmit);
        TrialStub next_trial;
        next_trial.fromJSON((*bit).toJSON());

        base.name+=next_trial.name;
        base.trial_type+=next_trial.trial_type;
        for(auto& v : next_trial.visual_stimuli){
            base.visual_stimuli.push_back(v);
        }
        for(auto& v : next_trial.auditory_stimuli){
            base.auditory_stimuli.push_back(v);
        }

        ttmit++;
    }
    return base.toJSON();
}

// update the order of the trials according to the order generated in the listWidget also for the
// updated JSON of espxerimental configuration, if any of the trials has been moved or displaced in the list
void MainWindow::updateTrialOrder()
{
    QList<TrialStub> reorderedTrials;
    for (int i = 0; i < ui->trialListWidget->count(); ++i) {
        QString itemName = ui->trialListWidget->item(i)->text();
        auto it = std::find_if(exp.trials.begin(), exp.trials.end(), [&itemName](const TrialStub& trial) {
            return QString::fromStdString(trial.name) == itemName;
        });
        if (it != exp.trials.end()) {
            reorderedTrials.push_back(*it);
        }
    }
    exp.trials = std::vector<TrialStub>(reorderedTrials.begin(), reorderedTrials.end());
    QVector<QString> reorderedFileNames;
    for (int i = 0; i < ui->trialListWidget->count(); ++i) {
        // trova il trial corrispondente
        QString name = ui->trialListWidget->item(i)->text();
        auto it = std::find_if(exp.trials.begin(), exp.trials.end(),
                               [&](auto& t){ return QString::fromStdString(t.name)==name; });
        int oldIdx = std::distance(exp.trials.begin(), it);
        reorderedFileNames.push_back(trialFileNames[oldIdx]);
    }
    trialFileNames = reorderedFileNames;
    refreshDisplay();

}

void MainWindow::on_trialVaddButton_clicked()
{
    TrialStub tr;
    tr.name = "V"+to_string(++vtnum);
    tr.duration = 5000;
    tr.trial_type="V";
    VisualStimulusStub vs;
    vs.controller_target="SLAVE1";
    vs.onset=500;
    vs.offset=1000;
    vs.pixeljson="[]";
    tr.visual_stimuli.push_back(vs);
    AddVDialog vdialog = AddVDialog(this,tr.toJSON());
    if(vdialog.exec()==QDialog::Accepted){
        string vjson = vdialog.getJSON();
        tr.reset();
        tr.fromJSON(vjson);
        exp.trials.push_back(tr);
        refreshDisplay();
    }
}


void MainWindow::on_applygeneralButton_clicked()
{
    refreshDisplay();
}

// function for show the content of the JSON configuration file fo the selected trial from the list
void MainWindow::on_trialListWidget_itemClicked(QListWidgetItem *item)
{
    int selected_index = ui->trialListWidget->indexFromItem(item).row();
    ui->trialviewEdit->clear();
    ui->trialviewEdit->appendPlainText(QString::fromStdString(exp.trials[selected_index].toJSON()));

}


void MainWindow::on_connectButton_clicked()
{
    refreshDisplay();
    try{
        std::cout << "[DEBUG] connection ok 1!" << std::endl;
        string server_address = ui->ipaddressEdit->text().toStdString();
        std::cout << "[DEBUG] ip : " << server_address << std::endl;
        asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(server_address,"13");
        std::cout << "[DEBUG] connection ok 2!" << std::endl;
        tcp::socket socket(io_context);
        std::cout << "[DEBUG] connection ok 3!" << std::endl;
        asio::connect(socket,endpoints);
        std::cout << "[DEBUG] connection ok 4!" << std::endl;
        // asio::ip::tcp socket(endpoints);
        // asio::streambuf b;
        // ostream os(&b);
        // os << "INTERFACE" << "#";
        asio::write(socket,asio::buffer("INTERFACE#"));
        // b.consume(b.size()+1);
        // os << exp.toJSON() << "#";
        asio::write(socket,asio::buffer(exp.toJSON()+"#"));
        // b.consume(b.size()+1);
        qDebug() << exp.toJSON();
    }
    catch(std::exception& e){
        std::cerr << "network error " << e.what() << "\n";
        // return false;
    }

}


void MainWindow::on_trialdeleteButton_clicked()
{
    auto selected_items = ui->trialListWidget->selectedItems();
    if(selected_items.size()==0) return;
    for(auto it = selected_items.begin();it!=selected_items.end();++it){
        auto trial = find_if(exp.trials.begin(),exp.trials.end(),[&](TrialStub& t){return t.name==(*it)->text().toStdString();});
        if(trial!=exp.trials.end()) exp.trials.erase(trial);
    }
    refreshDisplay();
}


void MainWindow::on_trialeditButton_clicked()
{
    auto selected_items = ui->trialListWidget->selectedItems();
    if(selected_items.size()==0) return;
    for(auto it = selected_items.begin();it!=selected_items.end();++it){
        auto trial = find_if(exp.trials.begin(),exp.trials.end(),[&](TrialStub& t){return t.name==(*it)->text().toStdString();});
        if(trial!=exp.trials.end()){
            EditTrialDialog etdialog = EditTrialDialog(this,(*trial).toJSON());
            if(etdialog.exec()==QDialog::Accepted){
                string trialjson = etdialog.getJSON();
                trial->fromJSON(trialjson);
                refreshDisplay();
            }
        }

    }
}


void MainWindow::on_combineButton_clicked()
{
    list<int> tomix;
    auto selected_items = ui->trialListWidget->selectedItems();
    for(auto it = selected_items.begin();it!=selected_items.end();++it){
        tomix.push_back(ui->trialListWidget->row(*it));
    }
    if(tomix.size()==0) return;
    string mixedtrialjson = getCombinedTrialJSON(tomix);
    TrialStub mixedtrial;
    mixedtrial.fromJSON(mixedtrialjson);
    exp.trials.push_back(mixedtrial);
    refreshDisplay();
}


void MainWindow::on_trialAaddButton_clicked()
{
    TrialStub tr;
    tr.name = "A"+to_string(++vtnum);
    tr.duration = 5000;
    tr.trial_type="A";
    AuditoryStimulusStub as;
    as.channel=6;
    as.onset=500;
    as.offset=1000;
    as.frequency=5000;
    as.duty_cycle=50;
    tr.auditory_stimuli.push_back(as);
    AddADialog adialog = AddADialog(this,tr.toJSON());
    if(adialog.exec()==QDialog::Accepted){
        string ajson = adialog.getJSON();
        tr.reset();
        tr.fromJSON(ajson);
        exp.trials.push_back(tr);
        refreshDisplay();
    }
}


// the trial is saved/exported as a novel file, even if it has already been saved previously
void MainWindow::on_exportButton_clicked()
{
    // 1. restore thre selected item from the list
    QListWidgetItem* selectedItem = ui->trialListWidget->currentItem();
    if(!selectedItem) return;

    // 2. find the index of the selected item
    int idx = ui->trialListWidget->row(selectedItem);
    QString defaultFileName = "./" + selectedItem->text();
    QString filename;
    filename = QFileDialog::getSaveFileName(this, tr("Save JSON"), defaultFileName, tr("JSON Files (*.json)"));
    if (filename.isEmpty()) return;

    QFile file(filename);
    // Open the file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Errore Salvataggio"),
                              tr("Impossibile aprire il file:\n%1").arg(filename));
        return;
    }
    // get the text inside the QPlainTextEdit related to the single selected trial from the trialListWidget
    QString jsonText = ui->trialviewEdit->toPlainText();
    // write the text in the file
    QTextStream out(&file);
    out << jsonText;
    // close the file
    file.close();
    
    // memorize the filepath in the parallel vector
    trialFileNames[idx] = filename;

    // memorize filepath on the item
    selectedItem->setData(Qt::UserRole, filename);

    statusBar()->showMessage(tr("Trial salvato in: %1").arg(filename), 3000);
}



void MainWindow::on_resetButton_clicked()
{
    ui->experimentaljsonEdit->clear();
    ui->trialListWidget->clear();
    ui->trialviewEdit->clear();
    exp.trials.clear();
    saveExpData();
    QString todisplay = QString::fromStdString(exp.toJSON());
    ui->experimentaljsonEdit->appendPlainText(todisplay);
}

// function for importation of a single trial/ a whole experimental configuration form ready JSON file
// void MainWindow::on_importButton_clicked()
// {
//     auto filenames = QFileDialog::getOpenFileNames(this,tr("Open JSON"), "./", tr("JSON Files (*.json *.txt)"));
//     for (const auto& filename : filenames){
//         importedFilename = filename;
//         string importjson = GC::getJSONStringFromFile(filename.toStdString()); // convert the file into a JSON string and save it into a string variable
//         if (filenames.size() == 1 || ui->trialviewEdit->toPlainText().isEmpty()) {
//             ui->trialviewEdit->setPlainText(importjson.c_str()); // write the content of the very first selected file into trialviewEdit widget
//         }

//         QFileInfo fileInfo(importedFilename);
//         QString baseName = fileInfo.baseName(); // obtain file name
//         ui->trialListWidget->addItem(baseName);
//         // export the json data content into the experimentaljsonEdit:
//         // to make this you need to understand how the json generated once the VDialog window is
//         // closed by the "OKAY" is then managed so that its content is automatically transferred and appended to the json
//         // inside experimentaljsonEdit, created according to ExperimentalStub istances. And moreover the name of the trial
//         // is added to che trialListWidget without creating crashing if Apply button is clicked
//         TrialStub tr;
//         tr.reset();
//         tr.fromJSON(importjson);
//         exp.trials.push_back(tr);
//         trialFileNames.push_back(filename);
//     }
//     refreshDisplay();
// }
void MainWindow::on_importButton_clicked()
{
    auto filenames = QFileDialog::getOpenFileNames(this, tr("Open JSON"), "./", tr("JSON Files (*.json *.txt)"));
    if (filenames.isEmpty()) return;

    // Mischia l'ordine dei file selezionati
    auto shuffledFilenames = GC::shuffledFileList(filenames);

    bool first = true;
    for (const auto& filename : shuffledFilenames) {
        importedFilename = filename;
        string importjson = GC::getJSONStringFromFile(filename.toStdString());

        if (first || ui->trialviewEdit->toPlainText().isEmpty()) {
            ui->trialviewEdit->setPlainText(importjson.c_str());
            first = false;
        }

        QFileInfo fileInfo(importedFilename);
        QString baseName = fileInfo.baseName();
        ui->trialListWidget->addItem(baseName);

        TrialStub tr;
        tr.reset();
        tr.fromJSON(importjson);
        exp.trials.push_back(tr);
        trialFileNames.push_back(filename);
    }

    refreshDisplay();
}



// the trial that have been imported or already soterd in a path is just overwritten on that file
void MainWindow::on_saveButton_clicked()
{
    auto* sel = ui->trialListWidget->currentItem();
    if (!sel) return;

    // Prendo obbligatoriamente il filepath associato all'item:
    QString filename = sel->data(Qt::UserRole).toString();
    if (filename.isEmpty()) {
        // Non c'è mai stato un "Save As" per questo trial:
        QMessageBox::warning(this,
                             tr("Save error"),
                             tr("Devi prima effettuare 'Export (Save As)' almeno una volta."));
        return;
    }

    QFile file(filename);
    // Open the file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::critical(this, tr("Save error"),
                              tr("Impossibile aprire il file:\n%1").arg(filename));
        return;
    }
    // get the text inside the QPlainTextEdit related to the single selected trial from the trialListWidget
    QString jsonText = ui->trialviewEdit->toPlainText();
    // write the text in the file
    QTextStream out(&file);
    out << jsonText;
    // close the file
    file.close();

    currentTrialFile = filename;
}
