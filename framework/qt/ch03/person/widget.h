#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qperson.h"

// 信号槽的过程:
// spinbox(valueChanged)->widget(on_spin_valueChanged)->
// person(ageChanged)->widget(on_ageChanged)

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QPerson *boy;
    QPerson *girl;

    Ui::Widget *ui;
private slots:
    void on_ageChanged(int value);
    void on_spin_valueChanged(int value);

    void on_pushBtnIncBoyAge_clicked();
    void on_pushBtnIncGirlAge_clicked();
    void on_pushBtnClassInfo_clicked();
};
#endif // WIDGET_H
