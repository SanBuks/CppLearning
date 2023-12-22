#ifndef DIALOG_CUSTOM_MAIN_WINDOW_H
#define DIALOG_CUSTOM_MAIN_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private slots:
  void on_actTab_SetSize_triggered();
 private:
  Ui::MainWindow *ui;
};

#endif