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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddVDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *controllerLabel;
    QLabel *onsetLabel;
    QLineEdit *offsetEdit;
    QComboBox *controlledEdit;
    QLineEdit *onsetEdit;
    QLabel *offsetLabel;
    QLineEdit *trialnameEdit;
    QLabel *label_2;
    QLabel *label_4;
    QLineEdit *trialdurationEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *imageLoadedButton;
    QPushButton *importjsonButton;
    QSpacerItem *horizontalSpacer;
    QCheckBox *imageloadedBox;
    QLabel *label;
    QLineEdit *pixeljsonEdit;
    QLabel *label_3;
    QPlainTextEdit *createjsonEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddVDialog)
    {
        if (AddVDialog->objectName().isEmpty())
            AddVDialog->setObjectName("AddVDialog");
        AddVDialog->resize(383, 560);
        verticalLayout = new QVBoxLayout(AddVDialog);
        verticalLayout->setObjectName("verticalLayout");
        frame = new QFrame(AddVDialog);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        controllerLabel = new QLabel(frame);
        controllerLabel->setObjectName("controllerLabel");

        gridLayout->addWidget(controllerLabel, 3, 0, 1, 1);

        onsetLabel = new QLabel(frame);
        onsetLabel->setObjectName("onsetLabel");

        gridLayout->addWidget(onsetLabel, 4, 0, 1, 1);

        offsetEdit = new QLineEdit(frame);
        offsetEdit->setObjectName("offsetEdit");

        gridLayout->addWidget(offsetEdit, 5, 2, 1, 1);

        controlledEdit = new QComboBox(frame);
        controlledEdit->addItem(QString());
        controlledEdit->addItem(QString());
        controlledEdit->setObjectName("controlledEdit");

        gridLayout->addWidget(controlledEdit, 3, 2, 1, 1);

        onsetEdit = new QLineEdit(frame);
        onsetEdit->setObjectName("onsetEdit");

        gridLayout->addWidget(onsetEdit, 4, 2, 1, 1);

        offsetLabel = new QLabel(frame);
        offsetLabel->setObjectName("offsetLabel");

        gridLayout->addWidget(offsetLabel, 5, 0, 1, 1);

        trialnameEdit = new QLineEdit(frame);
        trialnameEdit->setObjectName("trialnameEdit");

        gridLayout->addWidget(trialnameEdit, 0, 2, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 6, 0, 1, 1);

        trialdurationEdit = new QLineEdit(frame);
        trialdurationEdit->setObjectName("trialdurationEdit");

        gridLayout->addWidget(trialdurationEdit, 6, 2, 1, 1);


        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        imageLoadedButton = new QPushButton(AddVDialog);
        imageLoadedButton->setObjectName("imageLoadedButton");

        horizontalLayout->addWidget(imageLoadedButton);

        importjsonButton = new QPushButton(AddVDialog);
        importjsonButton->setObjectName("importjsonButton");

        horizontalLayout->addWidget(importjsonButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        imageloadedBox = new QCheckBox(AddVDialog);
        imageloadedBox->setObjectName("imageloadedBox");

        horizontalLayout->addWidget(imageloadedBox);


        verticalLayout->addLayout(horizontalLayout);

        label = new QLabel(AddVDialog);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label);

        pixeljsonEdit = new QLineEdit(AddVDialog);
        pixeljsonEdit->setObjectName("pixeljsonEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(3);
        sizePolicy1.setHeightForWidth(pixeljsonEdit->sizePolicy().hasHeightForWidth());
        pixeljsonEdit->setSizePolicy(sizePolicy1);
        pixeljsonEdit->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        pixeljsonEdit->setReadOnly(true);

        verticalLayout->addWidget(pixeljsonEdit);

        label_3 = new QLabel(AddVDialog);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        createjsonEdit = new QPlainTextEdit(AddVDialog);
        createjsonEdit->setObjectName("createjsonEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(createjsonEdit->sizePolicy().hasHeightForWidth());
        createjsonEdit->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(createjsonEdit);

        buttonBox = new QDialogButtonBox(AddVDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);

        QWidget::setTabOrder(trialnameEdit, controlledEdit);
        QWidget::setTabOrder(controlledEdit, onsetEdit);
        QWidget::setTabOrder(onsetEdit, offsetEdit);
        QWidget::setTabOrder(offsetEdit, trialdurationEdit);
        QWidget::setTabOrder(trialdurationEdit, imageLoadedButton);
        QWidget::setTabOrder(imageLoadedButton, importjsonButton);
        QWidget::setTabOrder(importjsonButton, pixeljsonEdit);
        QWidget::setTabOrder(pixeljsonEdit, createjsonEdit);
        QWidget::setTabOrder(createjsonEdit, imageloadedBox);

        retranslateUi(AddVDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, AddVDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AddVDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(AddVDialog);
    } // setupUi

    void retranslateUi(QDialog *AddVDialog)
    {
        AddVDialog->setWindowTitle(QCoreApplication::translate("AddVDialog", "Dialog", nullptr));
        controllerLabel->setText(QCoreApplication::translate("AddVDialog", "Controller target", nullptr));
        onsetLabel->setText(QCoreApplication::translate("AddVDialog", "Onset (ms)", nullptr));
        offsetEdit->setText(QCoreApplication::translate("AddVDialog", "1000", nullptr));
        controlledEdit->setItemText(0, QCoreApplication::translate("AddVDialog", "SLAVE1", nullptr));
        controlledEdit->setItemText(1, QCoreApplication::translate("AddVDialog", "SLAVE2", nullptr));

        onsetEdit->setText(QCoreApplication::translate("AddVDialog", "500", nullptr));
        offsetLabel->setText(QCoreApplication::translate("AddVDialog", "Offset (ms)", nullptr));
        trialnameEdit->setText(QCoreApplication::translate("AddVDialog", "V", nullptr));
        label_2->setText(QCoreApplication::translate("AddVDialog", "Trial name", nullptr));
        label_4->setText(QCoreApplication::translate("AddVDialog", "Trial duration (ms)", nullptr));
        imageLoadedButton->setText(QCoreApplication::translate("AddVDialog", "Load image", nullptr));
        importjsonButton->setText(QCoreApplication::translate("AddVDialog", "Import pixels text array", nullptr));
        imageloadedBox->setText(QCoreApplication::translate("AddVDialog", "Image loaded", nullptr));
        label->setText(QCoreApplication::translate("AddVDialog", "Loaded pixels json", nullptr));
        pixeljsonEdit->setText(QString());
        label_3->setText(QCoreApplication::translate("AddVDialog", "Create image", nullptr));
        createjsonEdit->setPlainText(QCoreApplication::translate("AddVDialog", "[]", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddVDialog: public Ui_AddVDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDVDIALOG_H
