/********************************************************************************
** Form generated from reading UI file 'edittrialdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditTrialDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *nameEdit;
    QLabel *nameLabel;
    QLineEdit *durationEdit;
    QLabel *durationLabel;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *addAButton;
    QPushButton *modifyAButton;
    QPushButton *deleteAButton;
    QListWidget *VstimulusList;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QPushButton *addVButton;
    QPushButton *modifyVButton;
    QPushButton *deleteVButton;
    QListWidget *AstimulusList;
    QLabel *label_2;
    QLabel *label;
    QFrame *line;
    QPlainTextEdit *trialJSONEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EditTrialDialog)
    {
        if (EditTrialDialog->objectName().isEmpty())
            EditTrialDialog->setObjectName("EditTrialDialog");
        EditTrialDialog->resize(504, 546);
        layoutWidget = new QWidget(EditTrialDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 481, 531));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        nameEdit = new QLineEdit(groupBox);
        nameEdit->setObjectName("nameEdit");

        gridLayout->addWidget(nameEdit, 0, 1, 1, 1);

        nameLabel = new QLabel(groupBox);
        nameLabel->setObjectName("nameLabel");

        gridLayout->addWidget(nameLabel, 0, 0, 1, 1);

        durationEdit = new QLineEdit(groupBox);
        durationEdit->setObjectName("durationEdit");

        gridLayout->addWidget(durationEdit, 1, 1, 1, 1);

        durationLabel = new QLabel(groupBox);
        durationLabel->setObjectName("durationLabel");

        gridLayout->addWidget(durationLabel, 1, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        frame_2 = new QFrame(groupBox_2);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        addAButton = new QPushButton(frame_2);
        addAButton->setObjectName("addAButton");

        verticalLayout_3->addWidget(addAButton);

        modifyAButton = new QPushButton(frame_2);
        modifyAButton->setObjectName("modifyAButton");

        verticalLayout_3->addWidget(modifyAButton);

        deleteAButton = new QPushButton(frame_2);
        deleteAButton->setObjectName("deleteAButton");

        verticalLayout_3->addWidget(deleteAButton);


        gridLayout_2->addWidget(frame_2, 1, 3, 1, 1);

        VstimulusList = new QListWidget(groupBox_2);
        VstimulusList->setObjectName("VstimulusList");

        gridLayout_2->addWidget(VstimulusList, 1, 1, 1, 1);

        frame = new QFrame(groupBox_2);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        addVButton = new QPushButton(frame);
        addVButton->setObjectName("addVButton");

        verticalLayout_2->addWidget(addVButton);

        modifyVButton = new QPushButton(frame);
        modifyVButton->setObjectName("modifyVButton");

        verticalLayout_2->addWidget(modifyVButton);

        deleteVButton = new QPushButton(frame);
        deleteVButton->setObjectName("deleteVButton");

        verticalLayout_2->addWidget(deleteVButton);


        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        AstimulusList = new QListWidget(groupBox_2);
        AstimulusList->setObjectName("AstimulusList");

        gridLayout_2->addWidget(AstimulusList, 1, 4, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_2, 0, 4, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label, 0, 1, 1, 1);

        line = new QFrame(groupBox_2);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_2->addWidget(line, 0, 2, 2, 1);


        verticalLayout->addWidget(groupBox_2);

        trialJSONEdit = new QPlainTextEdit(layoutWidget);
        trialJSONEdit->setObjectName("trialJSONEdit");

        verticalLayout->addWidget(trialJSONEdit);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);

        QWidget::setTabOrder(nameEdit, durationEdit);
        QWidget::setTabOrder(durationEdit, addVButton);
        QWidget::setTabOrder(addVButton, modifyVButton);
        QWidget::setTabOrder(modifyVButton, deleteVButton);
        QWidget::setTabOrder(deleteVButton, addAButton);
        QWidget::setTabOrder(addAButton, modifyAButton);
        QWidget::setTabOrder(modifyAButton, deleteAButton);
        QWidget::setTabOrder(deleteAButton, VstimulusList);
        QWidget::setTabOrder(VstimulusList, AstimulusList);
        QWidget::setTabOrder(AstimulusList, trialJSONEdit);

        retranslateUi(EditTrialDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, EditTrialDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, EditTrialDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(EditTrialDialog);
    } // setupUi

    void retranslateUi(QDialog *EditTrialDialog)
    {
        EditTrialDialog->setWindowTitle(QCoreApplication::translate("EditTrialDialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("EditTrialDialog", "General Information", nullptr));
        nameLabel->setText(QCoreApplication::translate("EditTrialDialog", "Trial name", nullptr));
        durationLabel->setText(QCoreApplication::translate("EditTrialDialog", "Trial duration (ms)", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("EditTrialDialog", "Stimuli", nullptr));
        addAButton->setText(QCoreApplication::translate("EditTrialDialog", "Add stimuus", nullptr));
        modifyAButton->setText(QCoreApplication::translate("EditTrialDialog", "Edit", nullptr));
        deleteAButton->setText(QCoreApplication::translate("EditTrialDialog", "Remove", nullptr));
        addVButton->setText(QCoreApplication::translate("EditTrialDialog", "Add stimulus", nullptr));
        modifyVButton->setText(QCoreApplication::translate("EditTrialDialog", "Edit...", nullptr));
        deleteVButton->setText(QCoreApplication::translate("EditTrialDialog", "Remove", nullptr));
        label_2->setText(QCoreApplication::translate("EditTrialDialog", "Auditory", nullptr));
        label->setText(QCoreApplication::translate("EditTrialDialog", "Visual", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditTrialDialog: public Ui_EditTrialDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITTRIALDIALOG_H
