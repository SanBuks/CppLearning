/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxFont;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxUnderline;
    QCheckBox *checkBoxBold;
    QCheckBox *checkBoxItalic;
    QGroupBox *groupBoxColour;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rBtnBlack;
    QRadioButton *rBtnRed;
    QRadioButton *rBtnBlue;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushBtnOk;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushBtnCancel;
    QPushButton *pushBtnClose;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(523, 369);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBoxFont = new QGroupBox(Dialog);
        groupBoxFont->setObjectName(QStringLiteral("groupBoxFont"));
        horizontalLayout = new QHBoxLayout(groupBoxFont);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBoxUnderline = new QCheckBox(groupBoxFont);
        checkBoxUnderline->setObjectName(QStringLiteral("checkBoxUnderline"));

        horizontalLayout->addWidget(checkBoxUnderline);

        checkBoxBold = new QCheckBox(groupBoxFont);
        checkBoxBold->setObjectName(QStringLiteral("checkBoxBold"));

        horizontalLayout->addWidget(checkBoxBold);

        checkBoxItalic = new QCheckBox(groupBoxFont);
        checkBoxItalic->setObjectName(QStringLiteral("checkBoxItalic"));

        horizontalLayout->addWidget(checkBoxItalic);


        verticalLayout->addWidget(groupBoxFont);

        groupBoxColour = new QGroupBox(Dialog);
        groupBoxColour->setObjectName(QStringLiteral("groupBoxColour"));
        horizontalLayout_2 = new QHBoxLayout(groupBoxColour);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        rBtnBlack = new QRadioButton(groupBoxColour);
        rBtnBlack->setObjectName(QStringLiteral("rBtnBlack"));

        horizontalLayout_2->addWidget(rBtnBlack);

        rBtnRed = new QRadioButton(groupBoxColour);
        rBtnRed->setObjectName(QStringLiteral("rBtnRed"));

        horizontalLayout_2->addWidget(rBtnRed);

        rBtnBlue = new QRadioButton(groupBoxColour);
        rBtnBlue->setObjectName(QStringLiteral("rBtnBlue"));

        horizontalLayout_2->addWidget(rBtnBlue);


        verticalLayout->addWidget(groupBoxColour);

        plainTextEdit = new QPlainTextEdit(Dialog);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushBtnOk = new QPushButton(Dialog);
        pushBtnOk->setObjectName(QStringLiteral("pushBtnOk"));

        horizontalLayout_3->addWidget(pushBtnOk);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushBtnCancel = new QPushButton(Dialog);
        pushBtnCancel->setObjectName(QStringLiteral("pushBtnCancel"));

        horizontalLayout_3->addWidget(pushBtnCancel);

        pushBtnClose = new QPushButton(Dialog);
        pushBtnClose->setObjectName(QStringLiteral("pushBtnClose"));

        horizontalLayout_3->addWidget(pushBtnClose);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Dialog);
        QObject::connect(pushBtnOk, SIGNAL(clicked()), Dialog, SLOT(accept()));
        QObject::connect(pushBtnCancel, SIGNAL(clicked()), Dialog, SLOT(reject()));
        QObject::connect(pushBtnClose, SIGNAL(clicked()), Dialog, SLOT(close()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        groupBoxFont->setTitle(QApplication::translate("Dialog", "Font", Q_NULLPTR));
        checkBoxUnderline->setText(QApplication::translate("Dialog", "Underline", Q_NULLPTR));
        checkBoxBold->setText(QApplication::translate("Dialog", "Bold", Q_NULLPTR));
        checkBoxItalic->setText(QApplication::translate("Dialog", "Italic", Q_NULLPTR));
        groupBoxColour->setTitle(QApplication::translate("Dialog", "Colour", Q_NULLPTR));
        rBtnBlack->setText(QApplication::translate("Dialog", "Black", Q_NULLPTR));
        rBtnRed->setText(QApplication::translate("Dialog", "Red", Q_NULLPTR));
        rBtnBlue->setText(QApplication::translate("Dialog", "Blue", Q_NULLPTR));
        plainTextEdit->setPlainText(QApplication::translate("Dialog", "Thy glass will show thee how thy beauties wear,\n"
"Thy dial how thy precious minutes waste;\n"
"The vacant leaves thy mind's imprint will bear,\n"
"And of this book this learning mayst thou taste.\n"
"The wrinkles which thy glass will truly show\n"
"Of mouthed graves will give thee memory;\n"
"Thou by thy dial's shady stealth mayst know\n"
"Time's thievish progress to eternity.\n"
"Look, what thy memory can not contain\n"
"Commit to these waste blanks, and thou shalt find\n"
"Those children nursed, deliver'd from thy brain,\n"
"To take a new acquaintance of thy mind.\n"
"These offices, so oft as thou wilt look,\n"
"Shall profit thee and much enrich thy book.", Q_NULLPTR));
        plainTextEdit->setPlaceholderText(QString());
        pushBtnOk->setText(QApplication::translate("Dialog", "Accept", Q_NULLPTR));
        pushBtnCancel->setText(QApplication::translate("Dialog", "Cancel", Q_NULLPTR));
        pushBtnClose->setText(QApplication::translate("Dialog", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
