#include "slabel.h"

#include <QEvent>
#include <QPalette>

Slabel::Slabel(QWidget *parent ) : QLabel(parent) {
  this->setAttribute(Qt::WA_Hover , true);
}

bool Slabel::event(QEvent *event) {
  if (event->type() == QEvent::HoverEnter) {
    QPalette palette = this->palette();
    palette.setColor(QPalette::ColorRole::WindowText, Qt::red);
    this->setPalette(palette);
  } else if (event->type() == QEvent::HoverLeave) {
    QPalette palette = this->palette();
    palette.setColor(QPalette::ColorRole::WindowText, Qt::black);
    this->setPalette(palette);
  }
  return QLabel::event(event);
}

void Slabel::mouseDoubleClickEvent(QMouseEvent *event) {
  Q_UNUSED(event)
  emit doubleClicked();
}



