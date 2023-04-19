#ifndef MISC_HEADER_WIDGET_H
#define MISC_HEADER_WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
 Q_OBJECT

 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget() override;
 private slots:
  void on_SliderRed_valueChanged(int value);
  void on_SliderH_valueChanged(int value);
  void on_SliderV_valueChanged(int value);
  void on_dial_valueChanged(int value);
  void on_radioBtnDec_clicked();
  void on_radioBtnBin_clicked();
  void on_radioBtnHex_clicked();
  void on_radioBtnOct_clicked();
 private:
  Ui::Widget *ui;
};

#endif //MISC_HEADER_WIDGET_H
