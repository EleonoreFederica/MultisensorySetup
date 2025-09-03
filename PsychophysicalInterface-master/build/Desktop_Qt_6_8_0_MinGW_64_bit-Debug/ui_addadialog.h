/********************************************************************************
** Form generated from reading UI file 'addadialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDADIALOG_H
#define UI_ADDADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddADialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLineEdit *trialtypeEdit;
    QLabel *label;
    QLabel *label_3;
    QLabel *offsetLabel;
    QLineEdit *cycleoffsetEdit;
    QLineEdit *dutycycleEdit;
    QLabel *label_6;
    QLineEdit *frequencyEdit;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_2;
    QLineEdit *onsetEdit;
    QLabel *onsetLabel;
    QLineEdit *offsetEdit;
    QLineEdit *channelEdit;
    QLineEdit *trialdurationEdit;
    QLabel *channelLabel;
    QLineEdit *trialnameEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddADialog)
    {
        if (AddADialog->objectName().isEmpty())
            AddADialog->setObjectName("AddADialog");
        AddADialog->resize(176, 278);
        verticalLayout = new QVBoxLayout(AddADialog);
        verticalLayout->setObjectName("verticalLayout");
        frame = new QFrame(AddADialog);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        trialtypeEdit = new QLineEdit(frame);
        trialtypeEdit->setObjectName("trialtypeEdit");

        gridLayout->addWidget(trialtypeEdit, 2, 2, 1, 1);

        label = new QLabel(frame);
        label->setObjectName("label");

        gridLayout->addWidget(label, 4, 0, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        offsetLabel = new QLabel(frame);
        offsetLabel->setObjectName("offsetLabel");

        gridLayout->addWidget(offsetLabel, 10, 0, 1, 1);

        cycleoffsetEdit = new QLineEdit(frame);
        cycleoffsetEdit->setObjectName("cycleoffsetEdit");

        gridLayout->addWidget(cycleoffsetEdit, 8, 2, 1, 1);

        dutycycleEdit = new QLineEdit(frame);
        dutycycleEdit->setObjectName("dutycycleEdit");

        gridLayout->addWidget(dutycycleEdit, 7, 2, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 8, 0, 1, 1);

        frequencyEdit = new QLineEdit(frame);
        frequencyEdit->setObjectName("frequencyEdit");

        gridLayout->addWidget(frequencyEdit, 6, 2, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 6, 0, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 7, 0, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        onsetEdit = new QLineEdit(frame);
        onsetEdit->setObjectName("onsetEdit");

        gridLayout->addWidget(onsetEdit, 9, 2, 1, 1);

        onsetLabel = new QLabel(frame);
        onsetLabel->setObjectName("onsetLabel");

        gridLayout->addWidget(onsetLabel, 9, 0, 1, 1);

        offsetEdit = new QLineEdit(frame);
        offsetEdit->setObjectName("offsetEdit");

        gridLayout->addWidget(offsetEdit, 10, 2, 1, 1);

        channelEdit = new QLineEdit(frame);
        channelEdit->setObjectName("channelEdit");

        gridLayout->addWidget(channelEdit, 5, 2, 1, 1);

        trialdurationEdit = new QLineEdit(frame);
        trialdurationEdit->setObjectName("trialdurationEdit");

        gridLayout->addWidget(trialdurationEdit, 4, 2, 1, 1);

        channelLabel = new QLabel(frame);
        channelLabel->setObjectName("channelLabel");

        gridLayout->addWidget(channelLabel, 5, 0, 1, 1);

        trialnameEdit = new QLineEdit(frame);
        trialnameEdit->setObjectName("trialnameEdit");

        gridLayout->addWidget(trialnameEdit, 0, 2, 1, 1);


        verticalLayout->addWidget(frame);

        buttonBox = new QDialogButtonBox(AddADialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);

        QWidget::setTabOrder(trialnameEdit, trialtypeEdit);
        QWidget::setTabOrder(trialtypeEdit, trialdurationEdit);
        QWidget::setTabOrder(trialdurationEdit, channelEdit);
        QWidget::setTabOrder(channelEdit, frequencyEdit);
        QWidget::setTabOrder(frequencyEdit, dutycycleEdit);
        QWidget::setTabOrder(dutycycleEdit, cycleoffsetEdit);
        QWidget::setTabOrder(cycleoffsetEdit, onsetEdit);
        QWidget::setTabOrder(onsetEdit, offsetEdit);

        retranslateUi(AddADialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, AddADialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AddADialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(AddADialog);
    } // setupUi

    void retranslateUi(QDialog *AddADialog)
    {
        AddADialog->setWindowTitle(QCoreApplication::translate("AddADialog", "Dialog", nullptr));
        trialtypeEdit->setText(QCoreApplication::translate("AddADialog", "A", nullptr));
        label->setText(QCoreApplication::translate("AddADialog", "Trial Duration", nullptr));
        label_3->setText(QCoreApplication::translate("AddADialog", "Trial Type", nullptr));
        offsetLabel->setText(QCoreApplication::translate("AddADialog", "Offset (ms)", nullptr));
        cycleoffsetEdit->setText(QCoreApplication::translate("AddADialog", "0", nullptr));
        dutycycleEdit->setText(QCoreApplication::translate("AddADialog", "50.0", nullptr));
        label_6->setText(QCoreApplication::translate("AddADialog", "Cycle Offset", nullptr));
        frequencyEdit->setText(QCoreApplication::translate("AddADialog", "4000", nullptr));
        label_4->setText(QCoreApplication::translate("AddADialog", "Frequency", nullptr));
        label_5->setText(QCoreApplication::translate("AddADialog", "Dut yCycle", nullptr));
        label_2->setText(QCoreApplication::translate("AddADialog", "Trial Name", nullptr));
        onsetEdit->setText(QCoreApplication::translate("AddADialog", "500", nullptr));
        onsetLabel->setText(QCoreApplication::translate("AddADialog", "Onset (ms)", nullptr));
        offsetEdit->setText(QCoreApplication::translate("AddADialog", "1000", nullptr));
        channelEdit->setText(QCoreApplication::translate("AddADialog", "6", nullptr));
        trialdurationEdit->setText(QCoreApplication::translate("AddADialog", "5000", nullptr));
        channelLabel->setText(QCoreApplication::translate("AddADialog", "Channel", nullptr));
        trialnameEdit->setText(QCoreApplication::translate("AddADialog", "A", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddADialog: public Ui_AddADialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDADIALOG_H
