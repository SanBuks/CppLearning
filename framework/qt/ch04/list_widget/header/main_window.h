#ifndef LIST_WIDGET__MAIN_WINDOW_H_
#define LIST_WIDGET__MAIN_WINDOW_H_

#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private slots:
  void on_toolBox_currentChanged(int index);
  void on_actListIni_triggered();
  void on_actListClear_triggered();
  void on_actListInsert_triggered();
  void on_actListAppend_triggered();
  void on_actListDelete_triggered();

  void on_actSelALL_triggered();
  void on_actSelNone_triggered();
  void on_actSelInvs_triggered();

  void on_chkBoxListEditable_clicked(bool checked);
  void on_listWidget_currentItemChanged(QListWidgetItem *current,
                                        QListWidgetItem *previous);
  void on_listWidget_customContextMenuRequested(const QPoint &pos);
 private:
  Ui::MainWindow *ui;
};

#endif //LIST_WIDGET__MAIN_WINDOW_H_
