#ifndef FILE_MODEL_VIEW__MAIN_WINDOW_H_
#define FILE_MODEL_VIEW__MAIN_WINDOW_H_

#include <QMainWindow>
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;
 private slots:
  void on_treeView_clicked(const QModelIndex &);
 private:
  Ui::MainWindow *ui;
  QFileSystemModel *file_model;

};

#endif //FILE_MODEL_VIEW__MAIN_WINDOW_H_
