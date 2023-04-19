#ifndef CBOX__WIDGET_H_
#define CBOX__WIDGET_H_

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
  void on_btnIniItems_clicked();
  void on_btnClearItems_clicked();
  void on_btnIni2_clicked();
  void on_comboBox_currentIndexChanged(const QString &);
  void on_comboBox2_currentIndexChanged(const QString &);
  void on_chkBoxEditable_clicked(bool);
  void on_btnClearText_clicked();
  void on_chkBoxReadonly_clicked(bool);
  void on_btnToComboBox_clicked();
  void on_plainTextEdit_customContextMenuRequested(const QPoint &);
 private:
  Ui::Widget *ui;
};

#endif //CBOX__WIDGET_H_
