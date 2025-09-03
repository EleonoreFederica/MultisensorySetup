#ifndef ADDVDIALOG_H
#define ADDVDIALOG_H

#include <QDialog>

#include "visualstimulusstub.h"
#include "trialstub.h"

namespace Ui {
class AddVDialog;
}

class AddVDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddVDialog(QWidget *parent = nullptr,string trialjsonstring="{}",int _vstimnumber=0);
    ~AddVDialog();


    bool loadFromJSON(string trialjsonstring);
    void refreshDisplay();
    void saveData();
    string getPixelJSONFromImage(QString filename);
    string getJSON();

    int vstimnumber;
    TrialStub trialstub;
    VisualStimulusStub vstub;


private slots:
    void on_imageLoadedButton_clicked();

    void on_importjsonButton_clicked();

private:
    Ui::AddVDialog *ui;

    string currentpixels;
};

#endif // ADDVDIALOG_H
