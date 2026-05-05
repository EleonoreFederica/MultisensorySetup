#ifndef EDITTRIALDIALOG_H
#define EDITTRIALDIALOG_H

#include <QDialog>
#include "trialstub.h"

namespace Ui {
class EditTrialDialog;
}

class EditTrialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTrialDialog(QWidget *parent = nullptr, string jsonstring="{}");
    ~EditTrialDialog();

    bool loadFromJSON(std::string jsonstring);
    bool loadFromTrial(TrialStub& trial);
    void refreshDisplay();
    void updateVisualOrder();
    void updateAuditoryOrder();
    string getJSON();


    TrialStub trialstub;
private slots:
    void on_addVButton_clicked();

    void on_modifyVButton_clicked();

    void on_deleteVButton_clicked();

    void on_addAButton_clicked();

    void on_deleteAButton_clicked();

    void on_modifyAButton_clicked();

private:
    Ui::EditTrialDialog *ui;
};

#endif // EDITTRIALDIALOG_H
