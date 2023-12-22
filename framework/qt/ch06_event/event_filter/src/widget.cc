#include "widget.h"
#include "ui_Widget.h"

#include <QPainter>
#include <QCloseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  ui->lab1->installEventFilter(this);
  ui->lab2->installEventFilter(this);
  ui->lab1->show();
  ui->lab2->show();
}

Widget::~Widget() {
  delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event) {
  if (watched == ui->lab1) {
    if (event->type() == QEvent::Enter) {
      ui->lab1->setStyleSheet("background-color: rgb(170, 255, 255);");
    } else if (event->type() == QEvent::Leave) {
      ui->lab1->setStyleSheet("");
      ui->lab1->setText("靠近我，点击我");
    } else if (event->type() == QEvent::MouseButtonPress) {
      ui->lab1->setText("button pressed");
    } else if (event->type() == QEvent::MouseButtonRelease){
      ui->lab1->setText("button released");
    }
  }

  if (watched == ui->lab2) {
    if (event->type() == QEvent::Enter) {
      ui->lab2->setStyleSheet("background-color: rgb(85, 255, 175);");
    } else if (event->type() == QEvent::Leave) {
      ui->lab2->setStyleSheet("");
      ui->lab2->setText("可以双击");
    } else if (event->type() == QEvent::MouseButtonDblClick) {
      ui->lab2->setText("double clicked");
    }
  }

  // 一定要注意传递给父组件，需要进行重新绘制
  return QWidget::eventFilter(watched, event);
}
