#include "widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  fTimer = new QTimer(this);
  fTimer->stop();
  fTimer->setInterval(1000);
  connect(fTimer, SIGNAL(timeout()),
          this, SLOT(on_timer_timeout()));

  fTimeCounter = new QTime;
}

Widget::~Widget() {
  delete ui;
  delete fTimeCounter;
}

void Widget::on_btnGetTime_clicked() {
  QDateTime cur = QDateTime::currentDateTime();

  ui->timeEdit->setTime(cur.time());
  ui->editTime->setText(cur.toString("hh:mm:ss"));

  ui->dateEdit->setDate(cur.date());
  ui->editDate->setText(cur.toString("yyyy-MM-dd"));

  ui->dateTimeEdit->setDateTime(cur);
  ui->editDateTime->setText(cur.toString("yyyy-MM-dd hh:mm:ss"));
}

void Widget::on_btnSetTime_clicked() {
  QString str = ui->editTime->text();
  str = str.trimmed();
  if (!str.isEmpty()) {
    QTime time = QTime::fromString(str, "hh:mm:ss");
    ui->timeEdit->setTime(time);
    ui->dateTimeEdit->setTime(time);
    auto temp = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->editDateTime->setText(temp);
  }
}

void Widget::on_calendarWidget_selectionChanged() {
  QDate dt = ui->calendarWidget->selectedDate();
  auto str = dt.toString("yyyy 年 MM 月 dd 日");
  ui->editCalendar->setText(str);
}

void Widget::on_btnSetDate_clicked() {
  QString str = ui->editDate->text();
  str = str.trimmed();
  if (!str.isEmpty()) {
    QDate date = QDate::fromString(str, "yyyy-MM-dd");
    ui->dateEdit->setDate(date);
    ui->dateTimeEdit->setDate(date);
    auto temp = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->editDateTime->setText(temp);
  }
}

void Widget::on_btnSetDateTime_clicked() {
  QString str = ui->editDateTime->text();
  str = str.trimmed();
  if (!str.isEmpty()) {
    QDateTime dateTime = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");

    ui->dateEdit->setDate(dateTime.date());
    ui->editDate->setText(dateTime.date().toString("yyyy-MM-dd"));

    ui->timeEdit->setTime(dateTime.time());
    ui->editTime->setText(dateTime.time().toString("hh:mm:ss"));

    ui->dateTimeEdit->setDateTime(dateTime);
  }
}

void Widget::on_timer_timeout() {
  QTime curTime = QTime::currentTime();
  ui->LCDHour->display(curTime.hour());
  ui->LCDMin->display(curTime.minute());
  ui->LCDSec->display(curTime.second());

  auto val = ui->progressBar->value();
  val++;
  if(val > 100) {
    val = 0;
  }
  ui->progressBar->setValue(val);
}

void Widget::on_btnSetIntv_clicked() {
  fTimer->setInterval(ui->spinBoxIntv->value());
}
void Widget::on_btnStart_clicked() {
  fTimer->start();
  fTimeCounter->start();
  ui->btnStart->setEnabled(false);
  ui->btnSetIntv->setEnabled(false);
  ui->btnStop->setEnabled(true);
}
void Widget::on_btnStop_clicked() {
  fTimer->stop();

  int tm = fTimeCounter->elapsed();
  int ms = tm % 1000;
  int sc = tm / 1000;
  QString str = QString::asprintf("流逝了 %d 秒 %d 毫秒", sc, ms);
  ui->LabElapsTime->setText(str);

  ui->btnStart->setEnabled(true);
  ui->btnSetIntv->setEnabled(true);
  ui->btnStop->setEnabled(false);
}
