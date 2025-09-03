#include "edittrialdialog.h"
#include "ui_edittrialdialog.h"

#include "gc.h"
#include "trialstub.h"
#include "addvdialog.h"
#include "addadialog.h"

#include <iostream>

EditTrialDialog::EditTrialDialog(QWidget *parent, string jsonstring)
    : QDialog(parent)
    , ui(new Ui::EditTrialDialog)
{
    this->setWindowTitle("Edit Trial");
    ui->setupUi(this);
    loadFromJSON(jsonstring);
    // ui->VstimulusList->setDragDropMode(QAbstractItemView::InternalMove); // define the drag-and-drop mode for modify the trials order in trialListWidget
    // connect(ui->VstimulusList->model(), &QAbstractItemModel::rowsMoved, this, &EditTrialDialog::updateVisualOrder);
    // ui->AstimulusList->setDragDropMode(QAbstractItemView::InternalMove); // define the drag-and-drop mode for modify the trials order in trialListWidget
    // connect(ui->AstimulusList->model(), &QAbstractItemModel::rowsMoved, this, &EditTrialDialog::updateAuditoryOrder);
}

EditTrialDialog::~EditTrialDialog()
{
    delete ui;
}

bool EditTrialDialog::loadFromJSON(std::string jsonstring)
{
    if(!trialstub.fromJSON(jsonstring)) return false;
    refreshDisplay();
    return true;
}

void EditTrialDialog::refreshDisplay()
{
    ui->nameEdit->setText(trialstub.name.c_str());
    ui->durationEdit->setText(to_string(trialstub.duration).c_str());
    //ui->trialtypeEdit->setText(trialstub.trial_type.c_str());
    ui->VstimulusList->clear();
    ui->AstimulusList->clear();


    for(int i=0;i<trialstub.visual_stimuli.size();i++){
        ui->VstimulusList->addItem(("Visual"+to_string(i)).c_str());
    }
    for(int i=0;i<trialstub.auditory_stimuli.size();i++){
        ui->AstimulusList->addItem(("Auditory"+to_string(i)).c_str());
    }
}

// // update the order of the stimuli according to the order generated in the listWidget
// // if any of the stimuli has been moved or displaced in the list
// void EditTrialDialog::updateAuditoryOrder()
// {
//     QList<AuditoryStimulusStub> reorderedStimuli;
//     for (int i = 0; i < ui->AstimulusList->count(); ++i) {
//         QString itemName = ui->AstimulusList->item(i)->text();
//         auto it = std::find_if(trialstub.auditory_stimuli.begin(), trialstub.auditory_stimuli.end(), [&itemName](const AuditoryStimulusStub& stimulus) {
//             return QString::fromStdString(stimulus.name) == itemName;
//         });
//         if (it != trialstub.auditory_stimuli.end()) {
//             reorderedStimuli.push_back(*it);
//         }
//     }
//     trialstub.auditory_stimuli = std::vector<AuditoryStimulusStub>(reorderedStimuli.begin(), reorderedStimuli.end());
// }

// // update the order of the stimuli according to the order generated in the listWidget
// // if any of the stimuli has been moved or displaced in the list
// void EditTrialDialog::updateVisualOrder()
// {
//     QList<VisualStimulusStub> reorderedStimuli;
//     for (int i = 0; i < ui->VstimulusList->count(); ++i) {
//         QString itemName = ui->VstimulusList->item(i)->text();
//         auto it = std::find_if(trialstub.visual_stimuli.begin(), trialstub.visual_stimuli.end(), [&itemName](const VisualStimulusStub& stimulus) {
//             return QString::fromStdString(stimulus.name) == itemName;
//         });
//         if (it != trialstub.visual_stimuli.end()) {
//             reorderedStimuli.push_back(*it);
//         }
//     }
//     trialstub.visual_stimuli = std::vector<VisualStimulusStub>(reorderedStimuli.begin(), reorderedStimuli.end());
// }
// }
string EditTrialDialog::getJSON()
{
    trialstub.name = ui->nameEdit->text().toStdString();
    trialstub.duration = ui->durationEdit->text().toInt();
    return trialstub.toJSON();
}

void EditTrialDialog::on_addVButton_clicked()
{
    VisualStimulusStub vs;
    vs.controller_target="SLAVE1";
    vs.onset=500;
    vs.offset=1000;
    vs.pixeljson="[]";
    trialstub.visual_stimuli.push_back(vs);
    int selectedV = trialstub.visual_stimuli.size()-1;
    AddVDialog vdialog = AddVDialog(this,trialstub.toJSON(),selectedV);
    if(vdialog.exec()==QDialog::Accepted){
        TrialStub tr;
        string newjson = vdialog.getJSON();
        tr.fromJSON(newjson);
        auto originV = tr.visual_stimuli.begin();
        advance(originV,selectedV);
        auto destinationV = trialstub.visual_stimuli.begin();
        advance(destinationV,selectedV);
        (*destinationV).fromJSON((*originV).toJSON());
        refreshDisplay();
    }
    else{
        trialstub.visual_stimuli.pop_back();
        refreshDisplay();
    }
}


void EditTrialDialog::on_modifyVButton_clicked()
{
    int selectedV = ui->VstimulusList->indexFromItem(ui->VstimulusList->currentItem()).row();
    if (!ui->VstimulusList->currentItem()) return;
    AddVDialog vdialog = AddVDialog(this,trialstub.toJSON(),selectedV);
    if(vdialog.exec()==QDialog::Accepted){
        TrialStub tr;
        string newjson = vdialog.getJSON();
        tr.fromJSON(newjson);
        auto originV = tr.visual_stimuli.begin();
        advance(originV,selectedV);
        auto destinationV = trialstub.visual_stimuli.begin();
        advance(destinationV,selectedV);
        (*destinationV).fromJSON((*originV).toJSON());
        refreshDisplay();
    }
}


void EditTrialDialog::on_deleteVButton_clicked()
{
    int selected_item = ui->VstimulusList->currentRow();
    if(((selected_item)<0)||(selected_item>=trialstub.visual_stimuli.size())) return;
    auto it = trialstub.visual_stimuli.begin();
    advance(it,selected_item);
    trialstub.visual_stimuli.erase(it);
    refreshDisplay();
}


void EditTrialDialog::on_addAButton_clicked()
{
    AuditoryStimulusStub as;
    as.channel=6;
    as.frequency=5000;
    as.duty_cycle=50.0;
    as.cycle_offset=0;
    as.onset=500;
    as.offset=1000;
    trialstub.auditory_stimuli.push_back(as);
    int selectedA = trialstub.auditory_stimuli.size()-1;
    AddADialog adialog = AddADialog(this,trialstub.toJSON(),selectedA);
    if(adialog.exec()==QDialog::Accepted){
        TrialStub tr;
        string newjson = adialog.getJSON();
        tr.fromJSON(newjson);
        auto originA = tr.auditory_stimuli.begin();
        advance(originA,selectedA);
        auto destinationA = trialstub.auditory_stimuli.begin();
        advance(destinationA,selectedA);
        (*destinationA).fromJSON((*originA).toJSON());
        refreshDisplay();
    }
    else{
        trialstub.auditory_stimuli.pop_back();
        refreshDisplay();
    }
}


void EditTrialDialog::on_deleteAButton_clicked()
{
    int selected_item = ui->AstimulusList->currentRow();
    if(((selected_item)<0)||(selected_item>=trialstub.auditory_stimuli.size())) return;
    auto it = trialstub.auditory_stimuli.begin();
    advance(it,selected_item);
    trialstub.auditory_stimuli.erase(it);
    refreshDisplay();
}


void EditTrialDialog::on_modifyAButton_clicked()
{
    int selectedA = ui->AstimulusList->indexFromItem(ui->AstimulusList->currentItem()).row();
    if (!ui->AstimulusList->currentItem()) return;
    AddADialog adialog = AddADialog(this,trialstub.toJSON(),selectedA);
    if(adialog.exec()==QDialog::Accepted){
        TrialStub tr;
        string newjson = adialog.getJSON();
        tr.fromJSON(newjson);
        auto originA = tr.auditory_stimuli.begin();
        advance(originA,selectedA);
        auto destinationA = trialstub.auditory_stimuli.begin();
        advance(destinationA,selectedA);
        (*destinationA).fromJSON((*originA).toJSON());
        refreshDisplay();
    }
}

