#ifndef EVENT_DEFAULT_UI_WIDGET_H_
#define EVENT_DEFAULT_UI_WIDGET_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget() override;
 protected:
  void mouseDoubleClickEvent(QMouseEvent *event) override;
 private slots:
  void onDoubleClicked();

 private:
  Ui::Widget *ui;
};

#endif //EVENT_DEFAULT_UI_WIDGET_H_
