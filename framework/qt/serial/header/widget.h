#ifndef SERIAL__WIDGET_H_
#define SERIAL__WIDGET_H_

#include <QWidget>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
 Q_OBJECT

 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget() override;

 private slots:
  void on_btnOpenPort_released();
  void on_readyRead();
  void on_btnSend_released();
 private:
  void init();

  QSerialPort port_;
  Ui::Widget *ui;

};

#endif //SERIAL__WIDGET_H_
