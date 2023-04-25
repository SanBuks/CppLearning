#include "include/painter_widget.h"
#include "ui_painter_widget.h"
#include <QPainter>
#include <QtMath>

PainterWidget::PainterWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::PainterWidget) {
  ui->setupUi(this);
  setPalette(QPalette(Qt::white));
  setAutoFillBackground(true);
  resize(400, 400);
}

PainterWidget::~PainterWidget() {
  delete ui;
}

void PainterWidget::paintEvent(QPaintEvent *event) {
//  painterBasic();
//  painterPath();
  painterView();
}

void PainterWidget::painterBasic() {
  // 初始化 QPainter, 指定 widget 为 QPaintDevice
  QPainter painter(this);
  // 设定渲染模式
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::TextAntialiasing);

  // 设定形状
  auto width = QPaintDevice::width();
  auto height = QPaintDevice::height();
  QRect rec(width/4, height/4, width/2, height/2);

  // 设定画笔
  QPen pen;
  pen.setWidth(10);                // 宽度
  pen.setColor(Qt::red);           // 颜色样式
  pen.setStyle(Qt::SolidLine);     // 实线样式
  pen.setCapStyle(Qt::FlatCap);    // 终端样式
  pen.setJoinStyle(Qt::BevelJoin); // 交点样式
  painter.setPen(pen);

  // 设定画刷
  QBrush brush;
  brush.setColor(Qt::yellow);       // 颜色
  brush.setStyle(Qt::SolidPattern); // 填充样式
  painter.setBrush(brush);

  // 画图像
  QImage q_image(":/images/image/qt.jpg");
  //painter.drawImage(rec, q_image);

  // 画字体
  QFont font;
  font.setPointSize(30);
  painter.setFont(font);
  //painter.drawText(rec, "font");

  // 画矩形
  //painter.drawRect(rec);

  // 画线段
  QPoint points[]{QPoint(width / 2, height / 2), QPoint(width / 2, height / 3),
                  QPoint(width / 3, height / 3),};
  painter.drawPolygon(points, 3);  // 不连成线
//painter.drawPolyline(points, 3); // 连成线
}

void PainterWidget::painterPath() {
  resize(1000, 300);

  // 初始化 QPainter, 指定 widget 为 QPaintDevice
  QPainter painter(this);
  // 设定渲染模式
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::TextAntialiasing);

  // 设定画刷
  QBrush brush;
  brush.setColor(Qt::yellow);       // 颜色
  brush.setStyle(Qt::SolidPattern); // 填充样式
  painter.setBrush(brush);

  // 画字体
  QFont font;
  font.setPointSize(10);
  painter.setFont(font);

  // 画五角星
  QPainterPath path;
  // 半径
  qreal r = 100;
  // 72度
  qreal radian = M_PI * 72 / 180;
  QPointF point_fs[]{
    QPointF(r * qCos(0 * radian), r * -qSin(0 * radian)),
    QPointF(r * qCos(1 * radian), r * -qSin(1 * radian)),
    QPointF(r * qCos(2 * radian), r * -qSin(2 * radian)),
    QPointF(r * qCos(3 * radian), r * -qSin(3 * radian)),
    QPointF(r * qCos(4 * radian), r * -qSin(4 * radian)),
  };
  path.moveTo(point_fs[0]);
  path.lineTo(point_fs[2]);
  path.lineTo(point_fs[4]);
  path.lineTo(point_fs[1]);
  path.lineTo(point_fs[3]);
  path.lineTo(point_fs[0]);
  path.closeSubpath();
  path.addText(point_fs[0], font, "1");
  path.addText(point_fs[1], font, "2");
  path.addText(point_fs[2], font, "3");
  path.addText(point_fs[3], font, "4");
  path.addText(point_fs[4], font, "5");

  // 保留状态
  painter.save();
  painter.translate(100, 120);
  painter.drawPath(path);
  painter.drawText(0, 0, "S1");

  // 恢复状态
  painter.restore();
  painter.translate(300, 120);
  painter.rotate(90);
  painter.scale(0.8, 0.8);
  painter.drawPath(path);
  painter.drawText(0, 0, "S2");

  // 重置状态
  painter.resetTransform();
  painter.translate(600, 120);
  painter.rotate(-90);
  painter.scale(1.2, 1.2);
  painter.drawPath(path);
  painter.drawText(0, 0, "S3");
}

void PainterWidget::painterView() {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::TextAntialiasing);

  // 取长宽最小值
  auto w = QPaintDevice::width();
  auto h = QPaintDevice::height();
  auto side = std::min(w, h);
  // 设定 viewPort 范围
  QRect rec((w - side) / 2, (h - side) / 2, side, side);
  painter.drawRect(rec);  // rec 也会相对变化
  painter.setViewport(rec);
  // 创建窗口, 逻辑坐标系中心为(0, 0), 左上角为 (-100, -100)
  painter.setWindow(-200, -200, 400, 400);

  QPen pen;
  pen.setWidth(1);
  pen.setColor(Qt::red);
  pen.setStyle(Qt::SolidLine);
  painter.setPen(pen);
  QLinearGradient linearGard(0, 0, 100, 0);
  linearGard.setColorAt(0, Qt::yellow);
  linearGard.setColorAt(1, Qt::green);
  linearGard.setSpread(QGradient::PadSpread);
  painter.setBrush(linearGard);
//  painter.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
  painter.setCompositionMode(QPainter::CompositionMode_Difference);
  for (int i = 0; i < 36; ++i) {
    painter.drawEllipse(0, -100, 200, 200);
    painter.rotate(10);
  }
}
