#include "header/m_graphics_view.h"
#include "ui_m_graphics_view.h"

#include <QMouseEvent>

MGraphicsView::MGraphicsView(QWidget *parent) :
   QGraphicsView(parent), ui(new Ui::MGraphicsView) {
  ui->setupUi(this);
}

MGraphicsView::~MGraphicsView() {
  delete ui;
}

void MGraphicsView::mousePressEvent(QMouseEvent *event) {
  if(event->button() == Qt::LeftButton) {
    auto point = event->pos();
    emit mouseClicked(point);
  }
  QGraphicsView::mousePressEvent(event);
}

void MGraphicsView::mouseDoubleClickEvent(QMouseEvent *event) {
  if(event->button() == Qt::LeftButton) {
    auto point = event->pos();
    emit mouseDoubleClick(point);
  }
  QGraphicsView::mouseDoubleClickEvent(event);
}

void MGraphicsView::mouseMoveEvent(QMouseEvent *event) {
  auto point = event->pos();
  emit mouseMovePoint(point);
  QGraphicsView::mouseMoveEvent(event);
}

void MGraphicsView::keyPressEvent(QKeyEvent *event) {
  emit keyPress(event);
  QGraphicsView::keyPressEvent(event);
}