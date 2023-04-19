/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *labBoyAge;
    QSpinBox *sBoxBoyAge;
    QPushButton *pushBtnIncBoyAge;
    QPushButton *pushBtnClassInfo;
    QLabel *labGirlAge;
    QSpinBox *sBoxGirlAge;
    QPushButton *pushBtnIncGirlAge;
    QPushButton *pushBtnClear;
    QPlainTextEdit *txtEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(319, 221);
        gridLayout_2 = new QGridLayout(Widget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labBoyAge = new QLabel(Widget);
        labBoyAge->setObjectName(QStringLiteral("labBoyAge"));

        gridLayout->addWidget(labBoyAge, 0, 0, 1, 1);

        sBoxBoyAge = new QSpinBox(Widget);
        sBoxBoyAge->setObjectName(QStringLiteral("sBoxBoyAge"));

        gridLayout->addWidget(sBoxBoyAge, 0, 1, 1, 1);

        pushBtnIncBoyAge = new QPushButton(Widget);
        pushBtnIncBoyAge->setObjectName(QStringLiteral("pushBtnIncBoyAge"));

        gridLayout->addWidget(pushBtnIncBoyAge, 0, 2, 1, 1);

        pushBtnClassInfo = new QPushButton(Widget);
        pushBtnClassInfo->setObjectName(QStringLiteral("pushBtnClassInfo"));

        gridLayout->addWidget(pushBtnClassInfo, 0, 3, 1, 1);

        labGirlAge = new QLabel(Widget);
        labGirlAge->setObjectName(QStringLiteral("labGirlAge"));

        gridLayout->addWidget(labGirlAge, 1, 0, 1, 1);

        sBoxGirlAge = new QSpinBox(Widget);
        sBoxGirlAge->setObjectName(QStringLiteral("sBoxGirlAge"));

        gridLayout->addWidget(sBoxGirlAge, 1, 1, 1, 1);

        pushBtnIncGirlAge = new QPushButton(Widget);
        pushBtnIncGirlAge->setObjectName(QStringLiteral("pushBtnIncGirlAge"));

        gridLayout->addWidget(pushBtnIncGirlAge, 1, 2, 1, 1);

        pushBtnClear = new QPushButton(Widget);
        pushBtnClear->setObjectName(QStringLiteral("pushBtnClear"));

        gridLayout->addWidget(pushBtnClear, 1, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        txtEdit = new QPlainTextEdit(Widget);
        txtEdit->setObjectName(QStringLiteral("txtEdit"));

        gridLayout_2->addWidget(txtEdit, 1, 0, 1, 1);


        retranslateUi(Widget);
        QObject::connect(pushBtnClear, SIGNAL(clicked()), txtEdit, SLOT(clear()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        labBoyAge->setText(QApplication::translate("Widget", "\350\256\276\347\275\256\347\224\267\345\255\251\345\271\264\351\276\204", Q_NULLPTR));
        pushBtnIncBoyAge->setText(QApplication::translate("Widget", "boy\351\225\277\345\244\247\344\270\200\345\262\201", Q_NULLPTR));
        pushBtnClassInfo->setText(QApplication::translate("Widget", "\347\261\273\345\257\271\350\261\241\344\277\241\346\201\257", Q_NULLPTR));
        labGirlAge->setText(QApplication::translate("Widget", "\350\256\276\347\275\256\345\245\263\345\255\251\345\271\264\351\276\204", Q_NULLPTR));
        pushBtnIncGirlAge->setText(QApplication::translate("Widget", "girl\351\225\277\345\244\247\344\270\200\345\262\201", Q_NULLPTR));
        pushBtnClear->setText(QApplication::translate("Widget", "\346\270\205\347\251\272\346\226\207\346\234\254\346\241\206", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
