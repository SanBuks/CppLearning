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
  // qsrand 是线程安全的
  qsrand(QTime::currentTime().msec());
  // 线程主循环
  while (!stop_) {
    if (!pause_) {
      // 写锁定
      QMutexLocker locker(&mutex_);
      dice_value_ = qrand() % 6 + 1;
      ++seq_;
    }
    msleep(1000);
  }
  quit();
}

bool DiceThread::ReadValue(int &seq, int &dice_value) {
  if (mutex_.tryLock()) {
    QMutexLocker locker(&mutex_);
    seq = seq_;
    dice_value = dice_value_;
    return true;
  } else {
    return false;
  }
}