#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ExperimentStub.h"
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void refreshDisplay();
    void saveExpData();
    void updateTrialOrder();

    string getCombinedTrialJSON(list<int> &trialstomix);

private slots:
    void on_trialVaddButton_clicked();
    void on_applygeneralButton_clicked();



    void on_trialListWidget_itemClicked(QListWidgetItem *item);

    void on_connectButton_clicked();

    void on_trialdeleteButton_clicked();

    void on_trialeditButton_clicked();

    void on_combineButton_clicked();

    void on_trialAaddButton_clicked();

    void on_exportButton_clicked();

    void on_resetButton_clicked();

    void on_importButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;

    ExperimentStub exp;


    int vtnum=0;
    int atnum=0;

    QString importedFilename;
    QString currentTrialFile;

    QVector<QString> trialFileNames;


};
#endif // MAINWINDOW_H
