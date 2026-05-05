/********************************************************************************
** Form generated from reading UI file 'addvdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDVDIALOG_H
#define UI_ADDVDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddVDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *trialtypeEdit;
    QLabel *onsetLabel;
    QLabel *offsetLabel;
    QLabel *controllerLabel;
    QLabel *label_2;
    QLineEdit *trialdurationEdit;
    QLineEdit *controlledEdit;
    QLabel *label;
    QLineEdit *offsetEdit;
    QLineEdit *onsetEdit;
    QLineEdit *trialnameEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *imageLoadedButton;
    QCheckBox *imageloadedBox;
    QLineEdit *pixeljsonEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddVDialog)
    {
        if (AddVDialog->objectName().isEmpty())
            AddVDialog->setObjectName("AddVDialog");
        AddVDialog->resize(258, 267);
        verticalLayout = new QVBoxLayout(AddVDialog);
        verticalLayout->setObjectName("verticalLayout");
        frame = new QFrame(AddVDialog);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        trialtypeEdit = new QLineEdit(frame);
        trialtypeEdit->setObjectName("trialtypeEdit");

        gridLayout->addWidget(trialtypeEdit, 2, 2, 1, 1);

        onsetLabel = new QLabel(frame);
        onsetLabel->setObjectName("onsetLabel");

        gridLayout->addWidget(onsetLabel, 6, 0, 1, 1);

        offsetLabel = new QLabel(frame);
        offsetLabel->setObjectName("offsetLabel");

        gridLayout->addWidget(offsetLabel, 7, 0, 1, 1);

        controllerLabel = new QLabel(frame);
        controllerLabel->setObjectName("controllerLabel");

        gridLayout->addWidget(controllerLabel, 5, 0, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        trialdurationEdit = new QLineEdit(frame);
        trialdurationEdit->setObjectName("trialdurationEdit");

        gridLayout->addWidget(trialdurationEdit, 4, 2, 1, 1);

        controlledEdit = new QLineEdit(frame);
        controlledEdit->setObjectName("controlledEdit");

        gridLayout->addWidget(controlledEdit, 5, 2, 1, 1);

        label = new QLabel(frame);
        label->setObjectName("label");

        gridLayout->addWidget(label, 4, 0, 1, 1);

        offsetEdit = new QLineEdit(frame);
        offsetEdit->setObjectName("offsetEdit");

        gridLayout->addWidget(offsetEdit, 7, 2, 1, 1);

        onsetEdit = new QLineEdit(frame);
        onsetEdit->setObjectName("onsetEdit");

        gridLayout->addWidget(onsetEdit, 6, 2, 1, 1);

        trialnameEdit = new QLineEdit(frame);
        trialnameEdit->setObjectName("trialnameEdit");

        gridLayout->addWidget(trialnameEdit, 0, 2, 1, 1);


        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        imageLoadedButton = new QPushButton(AddVDialog);
        imageLoadedButton->setObjectName("imageLoadedButton");

        horizontalLayout->addWidget(imageLoadedButton);

        imageloadedBox = new QCheckBox(AddVDialog);
        imageloadedBox->setObjectName("imageloadedBox");

        horizontalLayout->addWidget(imageloadedBox);


        verticalLayout->addLayout(horizontalLayout);

        pixeljsonEdit = new QLineEdit(AddVDialog);
        pixeljsonEdit->setObjectName("pixeljsonEdit");
        pixeljsonEdit->setReadOnly(true);

        verticalLayout->addWidget(pixeljsonEdit);

        buttonBox = new QDialogButtonBox(AddVDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);

        QWidget::setTabOrder(trialnameEdit, trialtypeEdit);
        QWidget::setTabOrder(trialtypeEdit, trialdurationEdit);
        QWidget::setTabOrder(trialdurationEdit, controlledEdit);
        QWidget::setTabOrder(controlledEdit, onsetEdit);
        QWidget::setTabOrder(onsetEdit, offsetEdit);
        QWidget::setTabOrder(offsetEdit, imageLoadedButton);
        QWidget::setTabOrder(imageLoadedButton, imageloadedBox);
        QWidget::setTabOrder(imageloadedBox, pixeljsonEdit);

        retranslateUi(AddVDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, AddVDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AddVDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(AddVDialog);
    } // setupUi

    void retranslateUi(QDialog *AddVDialog)
    {
        AddVDialog->setWindowTitle(QCoreApplication::translate("AddVDialog", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("AddVDialog", "Trial Type", nullptr));
        trialtypeEdit->setText(QCoreApplication::translate("AddVDialog", "V", nullptr));
        onsetLabel->setText(QCoreApplication::translate("AddVDialog", "Onset (ms)", nullptr));
        offsetLabel->setText(QCoreApplication::translate("AddVDialog", "Offset (ms)", nullptr));
        controllerLabel->setText(QCoreApplication::translate("AddVDialog", "Controller", nullptr));
        label_2->setText(QCoreApplication::translate("AddVDialog", "Trial Name", nullptr));
        trialdurationEdit->setText(QCoreApplication::translate("AddVDialog", "5000", nullptr));
        controlledEdit->setText(QCoreApplication::translate("AddVDialog", "SLAVE1", nullptr));
        label->setText(QCoreApplication::translate("AddVDialog", "Trial Duration", nullptr));
        offsetEdit->setText(QCoreApplication::translate("AddVDialog", "1000", nullptr));
        onsetEdit->setText(QCoreApplication::translate("AddVDialog", "500", nullptr));
        trialnameEdit->setText(QCoreApplication::translate("AddVDialog", "V", nullptr));
        imageLoadedButton->setText(QCoreApplication::translate("AddVDialog", "Load Image", nullptr));
        imageloadedBox->setText(QCoreApplication::translate("AddVDialog", "Loaded", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddVDialog: public Ui_AddVDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDVDIALOG_H
