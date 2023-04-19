//
// Created by San on 2023/4/12.
//

#ifndef DATE__WIDGET_H_
#define DATE__WIDGET_H_

#include <QWidget>
#include <QTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
 Q_OBJECT

 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget() override;

 private slots:
  void on_btnGetTime_clicked();
  void on_btnSetTime_clicked();
  void on_btnSetDate_clicked();
  void on_btnSetDateTime_clicked();

  void on_calendarWidget_selectionChanged();
  void on_timer_timeout();
  void on_btnSetIntv_clicked();
  void on_btnStart_clicked();
  void on_btnStop_clicked();
 private:
  QTimer *fTimer;
  QTime *fTimeCounter;
  Ui::Widget *ui;

};

#endif //DATE__WIDGET_H_
