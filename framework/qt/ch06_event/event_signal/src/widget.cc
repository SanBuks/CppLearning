#include "widget.h"
#include "ui_Widget.h"

#include <QPainter>
#include <QCloseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  // connect(ui->label, &Slabel::doubleClicked, this, &Widget::onDoubleClicked);
  connect(ui->label, SIGNAL(doubleClicked()), this, SLOT(onDoubleClicked()));
  // 连接 自定义组件类中的信号 指针形式会出现找不到的错误， 需要使用 字符串形式
}

Widget::~Widget() {
  delete ui;
}

void Widget::onDoubleClicked() {
  ui->label->setText("标签被双击了!");
  ui->label->adjustSize();
}
void Widget::mouseDoubleClickEvent(QMouseEvent *event) {
  ui->label->setText("窗口被双击了!");
  ui->label->adjustSize();
}
