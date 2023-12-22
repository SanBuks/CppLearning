#ifndef EVENT_DEFAULT_HEADER_SLABEL_H_
#define EVENT_DEFAULT_HEADER_SLABEL_H_


#include <QLabel>

class Slabel : public QLabel {
  Q_OBJECT
 public:
  Slabel(QWidget *parent);
 protected:
  bool event(QEvent *event) override;
 protected:
  void mouseDoubleClickEvent(QMouseEvent *event);
 signals:
  void doubleClicked();
};

#endif
