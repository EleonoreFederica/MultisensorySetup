/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *gridLayout;
    QLineEdit *subjectnameEdit;
    QCheckBox *writeoutputBox;
    QDoubleSpinBox *numloopSpinBox;
    QPushButton *applygeneralButton;
    QLabel *numloopsLabel;
    QLabel *subjectnameLabel;
    QLabel *ipLabel;
    QLineEdit *ipaddressEdit;
    QLabel *trialorderLabel;
    QComboBox *trialorderBox;
    QPlainTextEdit *experimentaljsonEdit;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QListWidget *trialListWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *trialVaddButton;
    QPushButton *trialAaddButton;
    QPushButton *trialdeleteButton;
    QPushButton *trialeditButton;
    QPushButton *combineButton;
    QPlainTextEdit *trialviewEdit;
    QPushButton *connectButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(769, 496);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(10, 10, 690, 441));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        subjectnameEdit = new QLineEdit(verticalLayoutWidget_3);
        subjectnameEdit->setObjectName("subjectnameEdit");

        gridLayout->addWidget(subjectnameEdit, 2, 1, 1, 1);

        writeoutputBox = new QCheckBox(verticalLayoutWidget_3);
        writeoutputBox->setObjectName("writeoutputBox");
        writeoutputBox->setChecked(true);
        writeoutputBox->setTristate(false);

        gridLayout->addWidget(writeoutputBox, 5, 0, 1, 1);

        numloopSpinBox = new QDoubleSpinBox(verticalLayoutWidget_3);
        numloopSpinBox->setObjectName("numloopSpinBox");
        numloopSpinBox->setDecimals(0);
        numloopSpinBox->setValue(1.000000000000000);

        gridLayout->addWidget(numloopSpinBox, 3, 1, 1, 1);

        applygeneralButton = new QPushButton(verticalLayoutWidget_3);
        applygeneralButton->setObjectName("applygeneralButton");

        gridLayout->addWidget(applygeneralButton, 6, 1, 1, 1);

        numloopsLabel = new QLabel(verticalLayoutWidget_3);
        numloopsLabel->setObjectName("numloopsLabel");

        gridLayout->addWidget(numloopsLabel, 3, 0, 1, 1);

        subjectnameLabel = new QLabel(verticalLayoutWidget_3);
        subjectnameLabel->setObjectName("subjectnameLabel");

        gridLayout->addWidget(subjectnameLabel, 2, 0, 1, 1);

        ipLabel = new QLabel(verticalLayoutWidget_3);
        ipLabel->setObjectName("ipLabel");

        gridLayout->addWidget(ipLabel, 0, 0, 1, 1);

        ipaddressEdit = new QLineEdit(verticalLayoutWidget_3);
        ipaddressEdit->setObjectName("ipaddressEdit");

        gridLayout->addWidget(ipaddressEdit, 0, 1, 1, 1);

        trialorderLabel = new QLabel(verticalLayoutWidget_3);
        trialorderLabel->setObjectName("trialorderLabel");

        gridLayout->addWidget(trialorderLabel, 4, 0, 1, 1);

        trialorderBox = new QComboBox(verticalLayoutWidget_3);
        trialorderBox->setObjectName("trialorderBox");

        gridLayout->addWidget(trialorderBox, 4, 1, 1, 1);


        horizontalLayout_6->addLayout(gridLayout);

        experimentaljsonEdit = new QPlainTextEdit(verticalLayoutWidget_3);
        experimentaljsonEdit->setObjectName("experimentaljsonEdit");
        experimentaljsonEdit->setMinimumSize(QSize(200, 0));

        horizontalLayout_6->addWidget(experimentaljsonEdit);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        trialListWidget = new QListWidget(verticalLayoutWidget_3);
        trialListWidget->setObjectName("trialListWidget");
        trialListWidget->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);

        verticalLayout_2->addWidget(trialListWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        trialVaddButton = new QPushButton(verticalLayoutWidget_3);
        trialVaddButton->setObjectName("trialVaddButton");

        horizontalLayout_2->addWidget(trialVaddButton);

        trialAaddButton = new QPushButton(verticalLayoutWidget_3);
        trialAaddButton->setObjectName("trialAaddButton");

        horizontalLayout_2->addWidget(trialAaddButton);

        trialdeleteButton = new QPushButton(verticalLayoutWidget_3);
        trialdeleteButton->setObjectName("trialdeleteButton");

        horizontalLayout_2->addWidget(trialdeleteButton);

        trialeditButton = new QPushButton(verticalLayoutWidget_3);
        trialeditButton->setObjectName("trialeditButton");

        horizontalLayout_2->addWidget(trialeditButton);

        combineButton = new QPushButton(verticalLayoutWidget_3);
        combineButton->setObjectName("combineButton");

        horizontalLayout_2->addWidget(combineButton);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_5->addLayout(verticalLayout_2);

        trialviewEdit = new QPlainTextEdit(verticalLayoutWidget_3);
        trialviewEdit->setObjectName("trialviewEdit");
        trialviewEdit->setMinimumSize(QSize(200, 200));

        horizontalLayout_5->addWidget(trialviewEdit);


        verticalLayout_3->addLayout(horizontalLayout_5);

        connectButton = new QPushButton(verticalLayoutWidget_3);
        connectButton->setObjectName("connectButton");

        verticalLayout_3->addWidget(connectButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 769, 18));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        subjectnameEdit->setText(QCoreApplication::translate("MainWindow", "subjectname", nullptr));
        writeoutputBox->setText(QCoreApplication::translate("MainWindow", "Write output", nullptr));
        applygeneralButton->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        numloopsLabel->setText(QCoreApplication::translate("MainWindow", "#loops", nullptr));
        subjectnameLabel->setText(QCoreApplication::translate("MainWindow", "Subject Name", nullptr));
        ipLabel->setText(QCoreApplication::translate("MainWindow", "IP Address:", nullptr));
        ipaddressEdit->setText(QCoreApplication::translate("MainWindow", "192.168.1.10", nullptr));
        trialorderLabel->setText(QCoreApplication::translate("MainWindow", "Trialordering", nullptr));
        trialVaddButton->setText(QCoreApplication::translate("MainWindow", "+V", nullptr));
        trialAaddButton->setText(QCoreApplication::translate("MainWindow", "+A", nullptr));
        trialdeleteButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        trialeditButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        combineButton->setText(QCoreApplication::translate("MainWindow", "mix", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect and Upload", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
