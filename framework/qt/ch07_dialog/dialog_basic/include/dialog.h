#ifndef DIALOG_BASIC_SRC_DIALOG_H_
#define DIALOG_BASIC_SRC_DIALOG_H_

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog {
  Q_OBJECT

 public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog() override;

 private slots:
  void on_btnClearText_clicked();
  void on_btnOpen_clicked();
  void on_btnOpenMulti_clicked();
  void on_btnSelDir_clicked();
  void on_btnSave_clicked();
  void on_btnColor_clicked();
  void on_btnFont_clicked();
  void on_btnInputString_clicked();
  void on_btnInputItem_clicked();
  void on_btnInputInt_clicked();
  void on_btnInputFloat_clicked();

  void on_btnMsgInformation_clicked();
  void on_btnMsgQuestion_clicked();
 private:
  Ui::Dialog *ui;
};

#endif
