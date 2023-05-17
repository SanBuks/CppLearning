#ifndef DICE_DIALOG_H_
#define DICE_DIALOG_H_


#include <QDialog>
#include <QTimer>
#include "dice_thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DiceDialog; }
QT_END_NAMESPACE

class DiceDialog : public QDialog {
 Q_OBJECT
 public:
  explicit DiceDialog(QWidget *parent = nullptr);
  ~DiceDialog() override;

 protected:
  void closeEvent(QCloseEvent *event) override;
 private slots:
  void on_btnStartThread_clicked();
  void on_btnStopThread_clicked();
  void on_btnDiceBegin_clicked();
  void on_btnDiceEnd_clicked();
  void on_btnClear_clicked();

  void onThreadStarted();
  void onThreadFinished();
  void onTimeOutReadNewValue();
 private:
  Ui::DiceDialog *ui;
  DiceThread thread_;
  int seq_;
  int dice_value_;
  QTimer timer_;
};

#endif
