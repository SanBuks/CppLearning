#include "include/mgraphics_view.h"
#include "ui_mgraphics_view.h"

#include <QMouseEvent>

MGraphicsView::MGraphicsView(QWidget *parent) :
    QGraphicsView(parent), ui(new Ui::MGraphicsView) {
  ui->setupUi(this);
}

MGraphicsView::~MGraphicsView() {
  delete ui;
}

// 鼠标左击事件
void MGraphicsView::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    // 获取位置地点
    QPoint point = event->pos();
    emit mouseClicked(point);
  }
  // 一定要调用父类的虚方法
  QGraphicsView::mousePressEvent(event);
}

void MGraphicsView::mouseMoveEvent(QMouseEvent *event) {
  auto point = event->pos();
  emit mouseMovePoint(point);
  QGraphicsView::mouseMoveEvent(event);
}
