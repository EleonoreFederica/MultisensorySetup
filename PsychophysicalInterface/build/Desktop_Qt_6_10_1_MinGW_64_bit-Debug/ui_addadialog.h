/********************************************************************************
** Form generated from reading UI file 'addadialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDADIALOG_H
#define UI_ADDADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddADialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *trialnameEdit;
    QLabel *channelLabel;
    QLineEdit *channelEdit;
    QLabel *label_4;
    QLineEdit *frequencyEdit;
    QLabel *label_5;
    QLineEdit *dutycycleEdit;
    QLabel *label_6;
    QLineEdit *cycleoffsetEdit;
    QLabel *onsetLabel;
    QLineEdit *onsetEdit;
    QLabel *offsetLabel;
    QLineEdit *offsetEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox;
    QLineEdit *trialdurationEdit;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddADialog)
    {
        if (AddADialog->objectName().isEmpty())
            AddADialog->setObjectName("AddADialog");
        AddADialog->resize(256, 318);
        verticalLayout = new QVBoxLayout(AddADialog);
        verticalLayout->setObjectName("verticalLayout");
        frame = new QFrame(AddADialog);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        formLayout = new QFormLayout(frame);
        formLayout->setObjectName("formLayout");
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_2);

        trialnameEdit = new QLineEdit(frame);
        trialnameEdit->setObjectName("trialnameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, trialnameEdit);

        channelLabel = new QLabel(frame);
        channelLabel->setObjectName("channelLabel");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, channelLabel);

        channelEdit = new QLineEdit(frame);
        channelEdit->setObjectName("channelEdit");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, channelEdit);

        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        frequencyEdit = new QLineEdit(frame);
        frequencyEdit->setObjectName("frequencyEdit");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, frequencyEdit);

        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_5);

        dutycycleEdit = new QLineEdit(frame);
        dutycycleEdit->setObjectName("dutycycleEdit");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, dutycycleEdit);

        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label_6);

        cycleoffsetEdit = new QLineEdit(frame);
        cycleoffsetEdit->setObjectName("cycleoffsetEdit");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, cycleoffsetEdit);

        onsetLabel = new QLabel(frame);
        onsetLabel->setObjectName("onsetLabel");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, onsetLabel);

        onsetEdit = new QLineEdit(frame);
        onsetEdit->setObjectName("onsetEdit");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, onsetEdit);

        offsetLabel = new QLabel(frame);
        offsetLabel->setObjectName("offsetLabel");

        formLayout->setWidget(7, QFormLayout::ItemRole::LabelRole, offsetLabel);

        offsetEdit = new QLineEdit(frame);
        offsetEdit->setObjectName("offsetEdit");

        formLayout->setWidget(7, QFormLayout::ItemRole::FieldRole, offsetEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        checkBox = new QCheckBox(frame);
        checkBox->setObjectName("checkBox");

        horizontalLayout_2->addWidget(checkBox);


        formLayout->setLayout(8, QFormLayout::ItemRole::SpanningRole, horizontalLayout_2);

        trialdurationEdit = new QLineEdit(frame);
        trialdurationEdit->setObjectName("trialdurationEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, trialdurationEdit);

        label = new QLabel(frame);
        label->setObjectName("label");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label);


        verticalLayout->addWidget(frame);

        buttonBox = new QDialogButtonBox(AddADialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);

        QWidget::setTabOrder(trialnameEdit, trialdurationEdit);
        QWidget::setTabOrder(trialdurationEdit, channelEdit);
        QWidget::setTabOrder(channelEdit, frequencyEdit);
        QWidget::setTabOrder(frequencyEdit, dutycycleEdit);
        QWidget::setTabOrder(dutycycleEdit, cycleoffsetEdit);
        QWidget::setTabOrder(cycleoffsetEdit, onsetEdit);
        QWidget::setTabOrder(onsetEdit, offsetEdit);
        QWidget::setTabOrder(offsetEdit, pushButton);
        QWidget::setTabOrder(pushButton, checkBox);

        retranslateUi(AddADialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, AddADialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AddADialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(AddADialog);
    } // setupUi

    void retranslateUi(QDialog *AddADialog)
    {
        AddADialog->setWindowTitle(QCoreApplication::translate("AddADialog", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("AddADialog", "Trial name", nullptr));
        trialnameEdit->setText(QCoreApplication::translate("AddADialog", "A", nullptr));
        channelLabel->setText(QCoreApplication::translate("AddADialog", "Channel", nullptr));
        channelEdit->setText(QCoreApplication::translate("AddADialog", "6", nullptr));
        label_4->setText(QCoreApplication::translate("AddADialog", "Frequency", nullptr));
        frequencyEdit->setText(QCoreApplication::translate("AddADialog", "5000", nullptr));
        label_5->setText(QCoreApplication::translate("AddADialog", "DutyCycle (%)", nullptr));
        dutycycleEdit->setText(QCoreApplication::translate("AddADialog", "50.0", nullptr));
        label_6->setText(QCoreApplication::translate("AddADialog", "CycleOffset", nullptr));
        cycleoffsetEdit->setText(QCoreApplication::translate("AddADialog", "0", nullptr));
        onsetLabel->setText(QCoreApplication::translate("AddADialog", "Onset (ms)", nullptr));
        onsetEdit->setText(QCoreApplication::translate("AddADialog", "500", nullptr));
        offsetLabel->setText(QCoreApplication::translate("AddADialog", "Offset (ms)", nullptr));
        offsetEdit->setText(QCoreApplication::translate("AddADialog", "1000", nullptr));
        pushButton->setText(QCoreApplication::translate("AddADialog", "Load sound...", nullptr));
        checkBox->setText(QCoreApplication::translate("AddADialog", "Loaded", nullptr));
        trialdurationEdit->setText(QCoreApplication::translate("AddADialog", "5000", nullptr));
        label->setText(QCoreApplication::translate("AddADialog", "Trial duration (ms)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddADialog: public Ui_AddADialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDADIALOG_H
