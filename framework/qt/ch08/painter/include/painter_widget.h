#ifndef PAINTER_PAINTER_WIDGET_H_
#define PAINTER_PAINTER_WIDGET_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class PainterWidget; }
QT_END_NAMESPACE

class PainterWidget : public QWidget {
 Q_OBJECT

 public:
  explicit PainterWidget(QWidget *parent = nullptr);
  ~PainterWidget() override;
  void paintEvent(QPaintEvent *event) override;

 private:
  Ui::PainterWidget *ui;

  // QPainter, QBrush 基本用法
  void painterBasic();

  // QPainterPath, 画五角星, 坐标转换
  void painterPath();

  // 窗口和视口关系
  void painterView();
};

#endif
