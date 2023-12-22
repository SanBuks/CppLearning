#ifndef GRAPHIC_VIEW_SOURCE_MGRAPHICS_VIEW_H_
#define GRAPHIC_VIEW_SOURCE_MGRAPHICS_VIEW_H_

#include <QGraphicsView>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MGraphicsView; }
QT_END_NAMESPACE

class MGraphicsView : public QGraphicsView {
 Q_OBJECT

 public:
  explicit MGraphicsView(QWidget *parent = nullptr);
  ~MGraphicsView() override;

  signals:
  void mouseMovePoint(QPoint point);
  void mouseClicked(QPoint point);
 protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
 private:
  Ui::MGraphicsView *ui;
  QLabel *labViewCord;
  QLabel *labSceneCord;
  QLabel *labItemCord;
  QLabel *labItemInfo;
  QGraphicsScene *scene;
};

#endif