#ifndef PLOT_SRC_MAIN_WINDOW_H_
#define PLOT_SRC_MAIN_WINDOW_H_

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QMainWindow;
class QLabel;
class QGraphicsScene;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private slots:
  void on_mouseMovePoint(QPoint point);
  void on_mouseClicked(QPoint point);
  void on_mouseDoubleClick(QPoint point);
  void on_keyPress(QKeyEvent *event);

  // 增加相应图形选项
  void on_actItem_Rect_triggered();
  void on_actItem_Ellipse_triggered();
  void on_actItem_Circle_triggered();
  void on_actItem_Line_triggered();
  void on_actItem_Polygon_triggered();
  void on_actItem_Triangle_triggered();
  void on_actItem_Text_triggered();
  // 放大缩小
  void on_actZoomIn_triggered();
  void on_actZoomOut_triggered();
  void on_actRestore_triggered();
  // 旋转
  void on_actRotateLeft_triggered();
  void on_actRotateRight_triggered();
  // 前置后置
  void on_actEdit_Front_triggered();
  void on_actEdit_Back_triggered();
  // 组合
  void on_actGroup_triggered();
  void on_actGroupBreak_triggered();
  // 删除
  void on_actEdit_Delete_triggered();

 private:
  template<typename T> void setBrushColor(T *item);
  template<typename T> void setPenColor(T *item);
  template<typename T> void setFontColor(T *item);
  static const int kItemId = 1;
  static const int kItemDesc = 2;

  Ui::MainWindow *ui;

  QLabel *labItemInfo;
  QGraphicsScene *scene;
  int seqNum = 0;
  int frontZ= 0;
  int backZ = 0;

};

#endif //PLOT_SRC_MAIN_WINDOW_H_
