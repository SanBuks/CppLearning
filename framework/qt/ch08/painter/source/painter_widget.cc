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
//  painterTest();
}

void PainterWidget::painterBasic() {
  // 初始化 QPainter, 指定 widget 为 QPaintDevice
  QPainter painter(this);
  // 初始化 painter 相关属性
  initPainter(painter);

  // 画矩形
  auto width = QPaintDevice::width();
  auto height = QPaintDevice::height();
  QRect rec(width/4, height/4, width/2, height/2);
  //painter.drawRect(rec);
  // 画图像
  QImage q_image(":/images/image/qt.jpg");
  //painter.drawImage(rec, q_image);
  // 画文字
  //painter.drawText(rec, "font");
  // 画线段
  QPoint points[]{QPoint(width / 2, height / 2), QPoint(width / 2, height / 3),
                  QPoint(width / 3, height / 3),};
  painter.drawPolygon(points, 3);  // 不连成线
//  painter.drawPolyline(points, 3); // 连成线
}

void PainterWidget::painterPath() {
  resize(1000, 300);

  QPainter painter(this);
  initPainter(painter);

  // 画五角星
  QPainterPath path;
  // 半径
  qreal r = 80;
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
  path.addText(point_fs[0], painter.font(), "1");
  path.addText(point_fs[1], painter.font(), "2");
  path.addText(point_fs[2], painter.font(), "3");
  path.addText(point_fs[3], painter.font(), "4");
  path.addText(point_fs[4], painter.font(), "5");

  // 保留 painter 状态
  painter.save();

  painter.translate(100, 120);
  painter.drawPath(path);
  painter.drawText(0, 0, "S1");

  // 恢复 painter 状态, 重置坐标系状态
  painter.restore();
  painter.resetTransform();
  painter.save();

  painter.translate(300, 120);
  painter.rotate(90);
  painter.scale(0.8, 0.8);
  painter.drawPath(path);
  painter.drawText(0, 0, "S2");

  painter.restore();
  painter.resetTransform();
  painter.save();

  painter.translate(600, 120);
  painter.rotate(-90);
  painter.scale(1.2, 1.2);
  painter.drawPath(path);
  painter.drawText(0, 0, "S3");

  painter.restore();
}

void PainterWidget::painterView() {
  QPainter painter(this);
  initPainter(painter);
  // 取长宽最小值
  auto w = QPaintDevice::width();
  auto h = QPaintDevice::height();
  auto side = std::min(w, h);
  // 设定视口范围, 随 widget 变化而变化
  QRect rec((w - side) / 2, (h - side) / 2, side, side);
  painter.drawRect(rec);
  painter.setViewport(rec);
  // 设定窗口范围, 逻辑坐标系中心为(0, 0), 左上角为 (-200, -200)
  painter.setWindow(-200, -200, 400, 400);
  for (int i = 0; i < 36; ++i) {
    // 之后所有的操作都基于逻辑坐标
    painter.drawEllipse(0, -100, 200, 200);
    painter.rotate(10);
  }
}

void PainterWidget::initPainter(QPainter &painter) {
  // 设定渲染
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::TextAntialiasing);
  // 设定画笔
  QPen pen;
  pen.setWidth(2);                 // 宽度
  pen.setColor(Qt::red);           // 颜色样式
  pen.setStyle(Qt::SolidLine);     // 实线样式
  pen.setCapStyle(Qt::FlatCap);    // 终端样式
  pen.setJoinStyle(Qt::BevelJoin); // 交点样式
  painter.setPen(pen);
  // 设定字体
  QFont font;
  font.setPointSize(15);
  painter.setFont(font);
  // 设定画刷和渐变模式
  QBrush brush;
  brush.setColor(Qt::yellow);                  // 颜色
  brush.setStyle(Qt::SolidPattern);            // 填充样式
  QLinearGradient linearGard(-200, 0, 200, 0); // 渐变模式 (-200, 0) -> (200, 0) 方向渐变
  linearGard.setColorAt(0, Qt::yellow);        // 在 开始位置 增加颜色停止点
  linearGard.setColorAt(1, Qt::green);         // 在 结束位置 增加颜色停止点
  linearGard.setSpread(QGradient::PadSpread);  // 设定发散方式
  painter.setBrush(linearGard);
  // 设定图形叠加模式
  //painter.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
  painter.setCompositionMode(QPainter::CompositionMode_Difference);
}