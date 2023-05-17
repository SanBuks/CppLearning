#include "dice_thread.h"

#include <QTime>

DiceThread::DiceThread()
    : seq_(0),
      dice_value_(0),
      pause_(true),
      stop_(false) {}

void DiceThread::DiceBegin() {
  pause_ = false;
}

void DiceThread::DicePause() {
  pause_ = true;
}

void DiceThread::StopThread() {
  stop_ = true;
}

void DiceThread::run() {
  // qsrand 是线程安全
  qsrand(QTime::currentTime().msec());
  // 循环线程
  while (!stop_) {
    if (!pause_) {
      dice_value_ = qrand() % 6 + 1;
      ++seq_;
      emit NewValue(seq_, dice_value_);
    }
    msleep(1000);
  }
  quit();
}
