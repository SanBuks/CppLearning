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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *labDemo;
    QPushButton *bntClose;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(488, 339);
        labDemo = new QLabel(Widget);
        labDemo->setObjectName(QStringLiteral("labDemo"));
        labDemo->setGeometry(QRect(100, 70, 301, 101));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(36);
        labDemo->setFont(font);
        bntClose = new QPushButton(Widget);
        bntClose->setObjectName(QStringLiteral("bntClose"));
        bntClose->setGeometry(QRect(260, 220, 151, 51));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(12);
        bntClose->setFont(font1);

        retranslateUi(Widget);
        QObject::connect(bntClose, SIGNAL(clicked()), Widget, SLOT(close()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        labDemo->setText(QApplication::translate("Widget", "Hello!Widget!", Q_NULLPTR));
        bntClose->setText(QApplication::translate("Widget", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
