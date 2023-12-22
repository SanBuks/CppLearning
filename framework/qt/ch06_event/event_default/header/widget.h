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
  void paintEvent(QPaintEvent *event) override;
  void closeEvent(QCloseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

  void hideEvent(QHideEvent *event) override;
  void showEvent(QShowEvent *event) override;
 private:
  Ui::Widget *ui;
};

#endif //EVENT_DEFAULT_UI_WIDGET_H_
