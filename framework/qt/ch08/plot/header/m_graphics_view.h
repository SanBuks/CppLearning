#ifndef PLOT_SRC_M_GRAPHICS_VIEW_H_
#define PLOT_SRC_M_GRAPHICS_VIEW_H_

#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class MGraphicsView; }
class QGraphicsView;
QT_END_NAMESPACE

class MGraphicsView : public QGraphicsView {
 Q_OBJECT

 public:
  explicit MGraphicsView(QWidget *parent = nullptr);
  ~MGraphicsView() override;

 signals:
  void mouseMovePoint(QPoint point);
  void mouseClicked(QPoint point);
  void mouseDoubleClick(QPoint point);
  void keyPress(QKeyEvent *event);

 protected:
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private:
  Ui::MGraphicsView *ui;
};

#endif //PLOT_SRC_M_GRAPHICS_VIEW_H_
