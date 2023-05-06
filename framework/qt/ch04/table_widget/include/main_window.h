#ifndef TABLE_WIDGET__MAIN_WINDOW_H_
#define TABLE_WIDGET__MAIN_WINDOW_H_

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QLabel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private:
  Ui::MainWindow *ui;

  QLabel *labCellIndex;
  QLabel *labCellType;
  QLabel *labStudID;
 public slots:
  void on_btnSetHeader_clicked()
};

#endif //TABLE_WIDGET__MAIN_WINDOW_H_
