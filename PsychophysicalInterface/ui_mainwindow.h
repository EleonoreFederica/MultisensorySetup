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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *gridLayout;
    QCheckBox *writeoutputBox;
    QLabel *subjectnameLabel;
    QLineEdit *subjectnameEdit;
    QLabel *ipLabel;
    QLineEdit *ipaddressEdit;
    QComboBox *trialorderBox;
    QDoubleSpinBox *numloopSpinBox;
    QLabel *trialorderLabel;
    QLabel *numloopsLabel;
    QPushButton *generateButton;
    QPushButton *applygeneralButton;
    QPlainTextEdit *experimentaljsonEdit;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QPushButton *trialVaddButton;
    QPushButton *trialAaddButton;
    QPushButton *combineButton;
    QPushButton *trialeditButton;
    QPushButton *trialdeleteButton;
    QPushButton *resetButton;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_2;
    QListWidget *trialListWidget;
    QPlainTextEdit *trialviewEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *importButton;
    QPushButton *exportButton;
    QPushButton *saveButton;
    QPushButton *connectButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(664, 634);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(4);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(20, -1, -1, -1);
        writeoutputBox = new QCheckBox(centralwidget);
        writeoutputBox->setObjectName("writeoutputBox");
        writeoutputBox->setChecked(true);
        writeoutputBox->setTristate(false);

        gridLayout->addWidget(writeoutputBox, 5, 0, 1, 1);

        subjectnameLabel = new QLabel(centralwidget);
        subjectnameLabel->setObjectName("subjectnameLabel");

        gridLayout->addWidget(subjectnameLabel, 2, 0, 1, 1);

        subjectnameEdit = new QLineEdit(centralwidget);
        subjectnameEdit->setObjectName("subjectnameEdit");

        gridLayout->addWidget(subjectnameEdit, 2, 1, 1, 1);

        ipLabel = new QLabel(centralwidget);
        ipLabel->setObjectName("ipLabel");

        gridLayout->addWidget(ipLabel, 0, 0, 1, 1);

        ipaddressEdit = new QLineEdit(centralwidget);
        ipaddressEdit->setObjectName("ipaddressEdit");

        gridLayout->addWidget(ipaddressEdit, 0, 1, 1, 1);

        trialorderBox = new QComboBox(centralwidget);
        trialorderBox->setObjectName("trialorderBox");

        gridLayout->addWidget(trialorderBox, 4, 1, 1, 1);

        numloopSpinBox = new QDoubleSpinBox(centralwidget);
        numloopSpinBox->setObjectName("numloopSpinBox");
        numloopSpinBox->setDecimals(0);
        numloopSpinBox->setValue(1.000000000000000);

        gridLayout->addWidget(numloopSpinBox, 3, 1, 1, 1);

        trialorderLabel = new QLabel(centralwidget);
        trialorderLabel->setObjectName("trialorderLabel");

        gridLayout->addWidget(trialorderLabel, 4, 0, 1, 1);

        numloopsLabel = new QLabel(centralwidget);
        numloopsLabel->setObjectName("numloopsLabel");

        gridLayout->addWidget(numloopsLabel, 3, 0, 1, 1);

        generateButton = new QPushButton(centralwidget);
        generateButton->setObjectName("generateButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(generateButton->sizePolicy().hasHeightForWidth());
        generateButton->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        generateButton->setFont(font);

        gridLayout->addWidget(generateButton, 6, 0, 1, 1);

        applygeneralButton = new QPushButton(centralwidget);
        applygeneralButton->setObjectName("applygeneralButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(applygeneralButton->sizePolicy().hasHeightForWidth());
        applygeneralButton->setSizePolicy(sizePolicy1);
        applygeneralButton->setFont(font);

        gridLayout->addWidget(applygeneralButton, 7, 1, 1, 1);


        horizontalLayout_6->addLayout(gridLayout);

        experimentaljsonEdit = new QPlainTextEdit(centralwidget);
        experimentaljsonEdit->setObjectName("experimentaljsonEdit");
        experimentaljsonEdit->setMinimumSize(QSize(200, 0));

        horizontalLayout_6->addWidget(experimentaljsonEdit);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        trialVaddButton = new QPushButton(centralwidget);
        trialVaddButton->setObjectName("trialVaddButton");

        verticalLayout->addWidget(trialVaddButton);

        trialAaddButton = new QPushButton(centralwidget);
        trialAaddButton->setObjectName("trialAaddButton");

        verticalLayout->addWidget(trialAaddButton);

        combineButton = new QPushButton(centralwidget);
        combineButton->setObjectName("combineButton");

        verticalLayout->addWidget(combineButton);

        trialeditButton = new QPushButton(centralwidget);
        trialeditButton->setObjectName("trialeditButton");

        verticalLayout->addWidget(trialeditButton);

        trialdeleteButton = new QPushButton(centralwidget);
        trialdeleteButton->setObjectName("trialdeleteButton");

        verticalLayout->addWidget(trialdeleteButton);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName("resetButton");

        verticalLayout->addWidget(resetButton);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        trialListWidget = new QListWidget(centralwidget);
        trialListWidget->setObjectName("trialListWidget");
        trialListWidget->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);

        verticalLayout_2->addWidget(trialListWidget);


        horizontalLayout_5->addLayout(verticalLayout_2);

        trialviewEdit = new QPlainTextEdit(centralwidget);
        trialviewEdit->setObjectName("trialviewEdit");
        trialviewEdit->setMinimumSize(QSize(200, 200));

        horizontalLayout_5->addWidget(trialviewEdit);

        horizontalLayout_5->setStretch(0, 1);

        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(10, 30, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        importButton = new QPushButton(centralwidget);
        importButton->setObjectName("importButton");

        horizontalLayout_3->addWidget(importButton);

        exportButton = new QPushButton(centralwidget);
        exportButton->setObjectName("exportButton");

        horizontalLayout_3->addWidget(exportButton);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");

        horizontalLayout_3->addWidget(saveButton);


        verticalLayout_3->addLayout(horizontalLayout_3);

        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName("connectButton");
        connectButton->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(connectButton->sizePolicy().hasHeightForWidth());
        connectButton->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        connectButton->setFont(font1);
        connectButton->setAutoFillBackground(true);
        connectButton->setCheckable(false);
        connectButton->setAutoExclusive(false);
        connectButton->setAutoDefault(false);
        connectButton->setFlat(false);

        verticalLayout_3->addWidget(connectButton);


        verticalLayout_4->addLayout(verticalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 664, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(ipaddressEdit, subjectnameEdit);
        QWidget::setTabOrder(subjectnameEdit, numloopSpinBox);
        QWidget::setTabOrder(numloopSpinBox, trialorderBox);
        QWidget::setTabOrder(trialorderBox, writeoutputBox);
        QWidget::setTabOrder(writeoutputBox, importButton);
        QWidget::setTabOrder(importButton, exportButton);
        QWidget::setTabOrder(exportButton, trialVaddButton);
        QWidget::setTabOrder(trialVaddButton, trialAaddButton);
        QWidget::setTabOrder(trialAaddButton, combineButton);
        QWidget::setTabOrder(combineButton, trialeditButton);
        QWidget::setTabOrder(trialeditButton, trialdeleteButton);
        QWidget::setTabOrder(trialdeleteButton, resetButton);
        QWidget::setTabOrder(resetButton, experimentaljsonEdit);
        QWidget::setTabOrder(experimentaljsonEdit, trialListWidget);
        QWidget::setTabOrder(trialListWidget, trialviewEdit);

        retranslateUi(MainWindow);

        connectButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        writeoutputBox->setText(QCoreApplication::translate("MainWindow", "Write output", nullptr));
        subjectnameLabel->setText(QCoreApplication::translate("MainWindow", "Subject Name", nullptr));
        subjectnameEdit->setText(QCoreApplication::translate("MainWindow", "subjectname", nullptr));
        ipLabel->setText(QCoreApplication::translate("MainWindow", "IP Address", nullptr));
        ipaddressEdit->setText(QCoreApplication::translate("MainWindow", "192.168.1.10", nullptr));
        trialorderLabel->setText(QCoreApplication::translate("MainWindow", "Trial ordering", nullptr));
        numloopsLabel->setText(QCoreApplication::translate("MainWindow", "Number of loops", nullptr));
        generateButton->setText(QCoreApplication::translate("MainWindow", "Generate list of trials", nullptr));
        applygeneralButton->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        trialVaddButton->setText(QCoreApplication::translate("MainWindow", "Add V trial", nullptr));
        trialAaddButton->setText(QCoreApplication::translate("MainWindow", "Add A  trial", nullptr));
        combineButton->setText(QCoreApplication::translate("MainWindow", "Mix", nullptr));
        trialeditButton->setText(QCoreApplication::translate("MainWindow", "Edit...", nullptr));
        trialdeleteButton->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        importButton->setText(QCoreApplication::translate("MainWindow", "Import trial...", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "Save as", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect and upload", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
