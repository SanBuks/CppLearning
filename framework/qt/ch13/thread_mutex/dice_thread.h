#ifndef DICE_THREAD_H_
#define DICE_THREAD_H_

#include <QThread>
#include <QMutex>

class DiceThread : public QThread {
  Q_OBJECT
 public:
  DiceThread();
  void DiceBegin();
  void DicePause();
  void StopThread();

  bool ReadValue(int &seq, int &dice_value);  // 读取数据
 protected:
  void run() override;
 private:
  int seq_;
  int dice_value_;
  bool pause_;    // 骰子状态
  bool stop_;     // 线程主循环状态
  QMutex mutex_;  // 互斥量
};

#endif
