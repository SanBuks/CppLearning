#include "dice_dialog.h"
#include "ui_dice_dialog.h"

DiceDialog::DiceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiceDialog),
    thread_(),
    seq_(0),
    dice_value_(-1),
    timer_() {
  ui->setupUi(this);

  connect(&thread_, &DiceThread::started, this, &DiceDialog::onThreadStarted);
  connect(&thread_, &DiceThread::finished, this, &DiceDialog::onThreadFinished);
  connect(&timer_, &QTimer::timeout, this, &DiceDialog::onTimeOutReadNewValue);
}

DiceDialog::~DiceDialog() {
  delete ui;
}

void DiceDialog::closeEvent(QCloseEvent *event) {
  if (thread_.isRunning()) {
    thread_.StopThread();
    thread_.wait();
  }
  event->accept();
}

void DiceDialog::onThreadStarted() {
  ui->LabA->setText("Thread 状态: thread started");
}

void DiceDialog::onThreadFinished() {
  ui->LabA->setText("Thread 状态: thread finished");
}

void DiceDialog::onTimeOutReadNewValue() {
  int temp_seq, temp_dice_value;
  bool valid = thread_.ReadValue(temp_seq, temp_dice_value);
  if (valid && temp_seq != seq_) {
    seq_ = temp_seq;
    dice_value_ = temp_dice_value;
    auto str = QString::asprintf("第 %d 次掷骰子, 点数为： %d", seq_, dice_value_);
    ui->plainTextEdit->appendPlainText(str);
    auto filename = QString::asprintf(":/dice/images/d%d.jpg", dice_value_);
    QPixmap pic(filename);
    ui->LabPic->setPixmap(pic);
  }
}

void DiceDialog::on_btnStartThread_clicked() {
  thread_.start();
  ui->btnStartThread->setEnabled(false);
  ui->btnStopThread->setEnabled(true);
  ui->btnDiceBegin->setEnabled(true);
  ui->btnDiceEnd->setEnabled(false);
}

void DiceDialog::on_btnStopThread_clicked() {
  thread_.StopThread();
  thread_.wait();
  ui->btnStartThread->setEnabled(true);
  ui->btnStopThread->setEnabled(false);
  ui->btnDiceBegin->setEnabled(false);
  ui->btnDiceEnd->setEnabled(false);
}

void DiceDialog::on_btnDiceBegin_clicked() {
  thread_.DiceBegin();
  timer_.start(100);
  ui->btnDiceBegin->setEnabled(false);
  ui->btnDiceEnd->setEnabled(true);
}

void DiceDialog::on_btnDiceEnd_clicked() {
  thread_.DicePause();
  timer_.stop();
  ui->btnDiceBegin->setEnabled(true);
  ui->btnDiceEnd->setEnabled(false);
}

void DiceDialog::on_btnClear_clicked() {
  ui->plainTextEdit->clear();
}