#ifndef GRAPHIC_VIEW_MAIN_WINDOW_H_
#define GRAPHIC_VIEW_MAIN_WINDOW_H_

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;
 protected:
  void resizeEvent(QResizeEvent *event) override;
 private slots:
  void on_mouseMovePoint(QPoint point);
  void on_mouseClicked(QPoint point);
 private:
  Ui::MainWindow *ui;

  QLabel *labViewCord;
  QLabel *labSceneCord;
  QLabel *labItemCord;
  QGraphicsScene *scene;

  void initGraphics();
};

#endif