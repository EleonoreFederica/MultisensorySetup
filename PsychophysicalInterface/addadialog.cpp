#include "addadialog.h"
#include "ui_addadialog.h"

AddADialog::AddADialog(QWidget *parent, string trialjsonstring, int _astimnumber)
    : QDialog(parent)
    , ui(new Ui::AddADialog)
{
    this->setWindowTitle("Add/Edit Auditory Trial/Stimulus");
    ui->setupUi(this);
    astimnumber=_astimnumber;
    loadFromJSON(trialjsonstring);
}

AddADialog::~AddADialog()
{
    delete ui;
}


bool AddADialog::loadFromJSON(string trialjsonstring)
{
    if(!trialstub.fromJSON(trialjsonstring)) return false;
    auto it = trialstub.auditory_stimuli.begin();
    advance(it,astimnumber);
    if(!astub.fromJSON((*it).toJSON())) return false;
    refreshDisplay();
    return true;
}


void AddADialog::refreshDisplay()
{
    ui->trialnameEdit->setText(trialstub.name.c_str());
    // ui->trialdurationEdit->setText(to_string(trialstub.duration).c_str());
    // ui->trialtypeEdit->setText(trialstub.trial_type.c_str());

    ui->channelEdit->clear();
    ui->onsetEdit->clear();
    ui->offsetEdit->clear();
    ui->frequencyEdit->clear();
    ui->dutycycleEdit->clear();
    ui->cycleoffsetEdit->clear();


    ui->channelEdit->setText(to_string(astub.channel).c_str());
    ui->onsetEdit->setText(to_string(astub.onset).c_str());
    ui->offsetEdit->setText(to_string(astub.offset).c_str());
    ui->frequencyEdit->setText(to_string(astub.frequency).c_str());
    ui->dutycycleEdit->setText(to_string(astub.duty_cycle).c_str());
    ui->cycleoffsetEdit->setText(to_string(astub.cycle_offset).c_str());

}

void AddADialog::saveData()
{
    trialstub.name = ui->trialnameEdit->text().toStdString();
    // trialstub.duration = ui->trialdurationEdit->text().toInt(0);
    // trialstub.trial_type = ui->trialtypeEdit->text().toStdString();

    astub.channel = ui->channelEdit->text().toInt(0);
    astub.onset = ui->onsetEdit->text().toInt(0);
    astub.offset = ui->offsetEdit->text().toInt(0);
    astub.frequency = ui->frequencyEdit->text().toInt(0);
    astub.duty_cycle = ui->dutycycleEdit->text().toFloat(0);
    astub.cycle_offset = ui->cycleoffsetEdit->text().toInt(0);

    auto it = trialstub.auditory_stimuli.begin();
    advance(it,astimnumber);
    trialstub.auditory_stimuli.insert(it,astub);
    trialstub.auditory_stimuli.erase(it);
}


string AddADialog::getJSON()
{
    saveData();
    trialstub.name = ui->trialnameEdit->text().toStdString();
    trialstub.duration = ui->trialdurationEdit->text().toInt();
    return trialstub.toJSON();
}
