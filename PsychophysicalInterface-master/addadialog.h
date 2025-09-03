#ifndef ADDADIALOG_H
#define ADDADIALOG_H

#include <QDialog>
#include "auditorystimulusstub.h"
#include "trialstub.h"

namespace Ui {
class AddADialog;
}

class AddADialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddADialog(QWidget *parent = nullptr,string trialjsonstring="{}",int _astimnumber=0);
    ~AddADialog();

    bool loadFromJSON(string trialjsonstring);
    void refreshDisplay();
    void saveData();
    string getPixelJSONFromImage(QString filename);
    string getJSON();

    int astimnumber;
    TrialStub trialstub;
    AuditoryStimulusStub astub;

private:
    Ui::AddADialog *ui;
};

#endif // ADDADIALOG_H
