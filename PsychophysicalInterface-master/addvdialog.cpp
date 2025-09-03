#include "addvdialog.h"
#include "ui_addvdialog.h"
#include "visualstimulusstub.h"
#include <QImage>
#include <iostream>
#include <QFileDialog>
#include "gc.h"


using namespace std;

AddVDialog::AddVDialog(QWidget *parent, string trialjsonstring, int _vstimnumber)
    : QDialog(parent)
    , ui(new Ui::AddVDialog),
    currentpixels("[]")
{
    this->setWindowTitle("Add/Edit Visual Trial/Stimulus");
    ui->setupUi(this);
    vstimnumber=_vstimnumber;
    loadFromJSON(trialjsonstring);
}


AddVDialog::~AddVDialog()
{
    delete ui;
}

// It loads data from a JSON string and uses it to populate the trialstub object and other elements of the class.
// If all operations are successful, the function returns true; otherwise, false.
bool AddVDialog::loadFromJSON(string trialjsonstring)
{
    if(!trialstub.fromJSON(trialjsonstring)) // The function first tries to load the JSON data into the trialstub using the fromJSON method of trialstub
        return false;
    auto it = trialstub.visual_stimuli.begin();
    advance(it,vstimnumber);
    if(!vstub.fromJSON((*it).toJSON()))
        return false;
    currentpixels = vstub.pixeljson;
    refreshDisplay();
    return true;
}


void AddVDialog::refreshDisplay()
{
    ui->trialnameEdit->setText(trialstub.name.c_str());
    ui->trialdurationEdit->setText(to_string(trialstub.duration).c_str());
    // ui->trialtypeEdit->setText(trialstub.trial_type.c_str());

    // ui->controlledEdit->clear();
    ui->onsetEdit->clear();
    ui->offsetEdit->clear();
    ui->pixeljsonEdit->clear();
    ui->imageloadedBox->setCheckState(Qt::Unchecked);


    ui->controlledEdit->setCurrentText(QString::fromStdString(vstub.controller_target));
    ui->onsetEdit->setText(to_string(vstub.onset).c_str());
    ui->offsetEdit->setText(to_string(vstub.offset).c_str());
    ui->pixeljsonEdit->setText(vstub.pixeljson.c_str());
    if(vstub.pixeljson!="[]") ui->imageloadedBox->setCheckState(Qt::Checked);

    ui->buttonBox[0].setFocus();

}

void AddVDialog::saveData()
{
    trialstub.name = ui->trialnameEdit->text().toStdString();
    // trialstub.duration = ui->trialdurationEdit->text().toInt(0);
    // trialstub.trial_type = ui->trialtypeEdit->text().toStdString();

    vstub.controller_target = ui->controlledEdit->currentText().toStdString();
    vstub.onset = ui->onsetEdit->text().toInt(0);
    vstub.offset = ui->offsetEdit->text().toInt(0);
    vstub.pixeljson = currentpixels;//ui->pixeljsonEdit->text().toStdString();

    auto it = trialstub.visual_stimuli.begin();
    advance(it,vstimnumber);
    trialstub.visual_stimuli.insert(it,vstub);
    trialstub.visual_stimuli.erase(it);

}

string AddVDialog::getPixelJSONFromImage(QString filename)
{
    QImage px(filename);
    ui->buttonBox[0].setEnabled(false);
    if(px.isNull()){ cout << "ERROR LOADING IMAGE \n"; return "";}
    else{
        // ui->pixeljsonEdit->setText(filename);
        string toreturn="[";
        bool thefirst=true;
        for(int x=0;x<px.width();x++){
            for(int y=0;y<px.height();y++){
                auto p = QColor(px.pixel(x,y));
                if(p!=Qt::black){
                    if(thefirst) thefirst=false; else toreturn+=",";
                    toreturn+="["+to_string(x)+","+to_string(y)+","+to_string(p.red())+","+to_string(p.green())+","+to_string(p.blue())+"]";
                }
            }
        }
        toreturn+="]";
        ui->imageloadedBox->setCheckState(Qt::Checked);
        ui->buttonBox[0].setEnabled(true);
        ui->pixeljsonEdit->setText(toreturn.c_str());
        currentpixels = toreturn;
        // loadAndValidateTrialJSON();

        return toreturn;
    }


}

// The function returns a JSON representation of the trialstub object.
string AddVDialog::getJSON()
{
    // loadAndValidateTrialJSON();
    saveData();
    trialstub.name = ui->trialnameEdit->text().toStdString();
    trialstub.duration = ui->trialdurationEdit->text().toInt();
    return trialstub.toJSON();
}



void AddVDialog::on_imageLoadedButton_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this,tr("Open Image"), "./", tr("Image Files (*.png *.jpg *.bmp)"));
    getPixelJSONFromImage(filename);
    ui->buttonBox[0].setEnabled(true);
    ui->buttonBox[0].setFocus();

}





void AddVDialog::on_importjsonButton_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this,tr("Open JSON"), "./", tr("JSON Files (*.json *.txt)"));
    string importjson = GC::getJSONStringFromFile(filename.toStdString());
    ui->imageloadedBox->setCheckState(Qt::Checked);
    ui->buttonBox[0].setEnabled(true);
    ui->pixeljsonEdit->setText(importjson.c_str());
}


