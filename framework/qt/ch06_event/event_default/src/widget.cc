#include "widget.h"
#include "ui_Widget.h"

#include <QPainter>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() {
  delete ui;
}

void Widget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  QPainter painter(this);
  painter.drawPixmap(0, 0, this->width(), this->height(),
                     QPixmap(":/pics/images/background.jpg"));
}

void Widget::closeEvent(QCloseEvent *event) {
  QString dlg_title = "消息框";
  QString dlg_info = "确认退出吗?";
  QMessageBox::StandardButton result = QMessageBox::question(this, dlg_title, dlg_info,
                                                             QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
  if (result == QMessageBox::StandardButton::Yes) {
    event->accept();
  } else {
    event->ignore();
  }
}

void Widget::keyPressEvent(QKeyEvent *event) {
  auto point = ui->btnMove->pos();  // holds the position of the widget within its parent widget
  if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) {
    ui->btnMove->move(point.x() - 20, point.y());
  } else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) {
    ui->btnMove->move(point.x() + 20, point.y());
  } else if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up) {
    ui->btnMove->move(point.x(), point.y() - 20);
  } else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) {
    ui->btnMove->move(point.x(), point.y() + 20);
  }
  event->accept();
}

void Widget::hideEvent(QHideEvent *event) {
  Q_UNUSED(event)
  qDebug() << "隐藏事件触发";
}

void Widget::showEvent(QShowEvent *event) {
  Q_UNUSED(event)
  qDebug() << "显示事件触发";
}

void Widget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::MouseButton::LeftButton) {
    auto pos = event->pos();
    auto global_pos = event->globalPos();

    auto screen_pos = event->screenPos();
    auto local_pos = event->localPos();
    auto window_pos = event->windowPos();

    QString str = QString::asprintf("pos()=(%d,%d)", pos.x(), pos.y());                    // 父组件 相对坐标
    str += QString::asprintf("\nglobalPos()=(%.0f,%.0f)", global_pos.x(), global_pos.y());
    str += QString::asprintf("\nscreenPos()=(%.0f,%.0f)", screen_pos.x(), screen_pos.y()); // 屏幕 绝对坐标
    str += QString::asprintf("\nlocalPos()=(%.0f,%.0f)", local_pos.x(), local_pos.y());
    str += QString::asprintf("\nwindowPos()=(%.0f,%.0f)", window_pos.x(), window_pos.y());

    ui->labMove->setText(str);
    ui->labMove->adjustSize();
    ui->labMove->move(event->pos());
  }
  QWidget::mousePressEvent(event);
}
