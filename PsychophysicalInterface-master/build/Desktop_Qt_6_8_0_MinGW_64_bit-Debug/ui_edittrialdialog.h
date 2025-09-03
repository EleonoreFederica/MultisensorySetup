/********************************************************************************
** Form generated from reading UI file 'edittrialdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITTRIALDIALOG_H
#define UI_EDITTRIALDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditTrialDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *nameLabel;
    QLabel *durationLabel;
    QLabel *trialtypeLabel;
    QLineEdit *nameEdit;
    QLineEdit *trialtypeEdit;
    QLineEdit *durationEdit;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QListWidget *AstimulusList;
    QListWidget *VstimulusList;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *addVButton;
    QPushButton *deleteVButton;
    QPushButton *modifyVButton;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addAButton;
    QPushButton *deleteAButton;
    QPushButton *modifyAButton;
    QPlainTextEdit *trialJSONEdit;

    void setupUi(QDialog *EditTrialDialog)
    {
        if (EditTrialDialog->objectName().isEmpty())
            EditTrialDialog->setObjectName("EditTrialDialog");
        EditTrialDialog->resize(400, 405);
        buttonBox = new QDialogButtonBox(EditTrialDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(50, 370, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(EditTrialDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 0, 381, 111));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        nameLabel = new QLabel(groupBox);
        nameLabel->setObjectName("nameLabel");

        gridLayout->addWidget(nameLabel, 0, 0, 1, 1);

        durationLabel = new QLabel(groupBox);
        durationLabel->setObjectName("durationLabel");

        gridLayout->addWidget(durationLabel, 2, 0, 1, 1);

        trialtypeLabel = new QLabel(groupBox);
        trialtypeLabel->setObjectName("trialtypeLabel");

        gridLayout->addWidget(trialtypeLabel, 1, 0, 1, 1);

        nameEdit = new QLineEdit(groupBox);
        nameEdit->setObjectName("nameEdit");

        gridLayout->addWidget(nameEdit, 0, 1, 1, 1);

        trialtypeEdit = new QLineEdit(groupBox);
        trialtypeEdit->setObjectName("trialtypeEdit");

        gridLayout->addWidget(trialtypeEdit, 1, 1, 1, 1);

        durationEdit = new QLineEdit(groupBox);
        durationEdit->setObjectName("durationEdit");

        gridLayout->addWidget(durationEdit, 2, 1, 1, 1);

        groupBox_2 = new QGroupBox(EditTrialDialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 120, 381, 171));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        AstimulusList = new QListWidget(groupBox_2);
        AstimulusList->setObjectName("AstimulusList");

        gridLayout_2->addWidget(AstimulusList, 0, 1, 1, 1);

        VstimulusList = new QListWidget(groupBox_2);
        VstimulusList->setObjectName("VstimulusList");

        gridLayout_2->addWidget(VstimulusList, 0, 0, 1, 1);

        frame = new QFrame(groupBox_2);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName("horizontalLayout");
        addVButton = new QPushButton(frame);
        addVButton->setObjectName("addVButton");

        horizontalLayout->addWidget(addVButton);

        deleteVButton = new QPushButton(frame);
        deleteVButton->setObjectName("deleteVButton");

        horizontalLayout->addWidget(deleteVButton);

        modifyVButton = new QPushButton(frame);
        modifyVButton->setObjectName("modifyVButton");

        horizontalLayout->addWidget(modifyVButton);


        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        frame_2 = new QFrame(groupBox_2);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        addAButton = new QPushButton(frame_2);
        addAButton->setObjectName("addAButton");

        horizontalLayout_2->addWidget(addAButton);

        deleteAButton = new QPushButton(frame_2);
        deleteAButton->setObjectName("deleteAButton");

        horizontalLayout_2->addWidget(deleteAButton);

        modifyAButton = new QPushButton(frame_2);
        modifyAButton->setObjectName("modifyAButton");

        horizontalLayout_2->addWidget(modifyAButton);


        gridLayout_2->addWidget(frame_2, 1, 1, 1, 1);

        trialJSONEdit = new QPlainTextEdit(EditTrialDialog);
        trialJSONEdit->setObjectName("trialJSONEdit");
        trialJSONEdit->setGeometry(QRect(10, 300, 381, 64));

        retranslateUi(EditTrialDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, EditTrialDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, EditTrialDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(EditTrialDialog);
    } // setupUi

    void retranslateUi(QDialog *EditTrialDialog)
    {
        EditTrialDialog->setWindowTitle(QCoreApplication::translate("EditTrialDialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("EditTrialDialog", "General Information", nullptr));
        nameLabel->setText(QCoreApplication::translate("EditTrialDialog", "Name", nullptr));
        durationLabel->setText(QCoreApplication::translate("EditTrialDialog", "Duration", nullptr));
        trialtypeLabel->setText(QCoreApplication::translate("EditTrialDialog", "Trial Type", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("EditTrialDialog", "Stimuli", nullptr));
        addVButton->setText(QCoreApplication::translate("EditTrialDialog", "+", nullptr));
        deleteVButton->setText(QCoreApplication::translate("EditTrialDialog", "-", nullptr));
        modifyVButton->setText(QCoreApplication::translate("EditTrialDialog", "...", nullptr));
        addAButton->setText(QCoreApplication::translate("EditTrialDialog", "+", nullptr));
        deleteAButton->setText(QCoreApplication::translate("EditTrialDialog", "-", nullptr));
        modifyAButton->setText(QCoreApplication::translate("EditTrialDialog", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditTrialDialog: public Ui_EditTrialDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITTRIALDIALOG_H
