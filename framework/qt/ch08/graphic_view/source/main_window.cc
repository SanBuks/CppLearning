#include "include/main_window.h"
#include "ui_main_window.h"

#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  initGraphics();

  labViewCord = new QLabel("View 坐标:");
  labViewCord->setMinimumWidth(150);
  ui->statusbar->addWidget(labViewCord);

  labSceneCord = new QLabel("Scene 坐标:");
  labSceneCord->setMinimumWidth(150);
  ui->statusbar->addWidget(labSceneCord);

  labItemCord = new QLabel("Item 坐标:");
  labItemCord->setMinimumWidth(150);
  ui->statusbar->addWidget(labItemCord);

  ui->graphicsView->setMouseTracking(true);
  ui->graphicsView->setCursor(Qt::CrossCursor);
  ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

  connect(ui->graphicsView, &MGraphicsView::mouseMovePoint,
          this, &MainWindow::on_mouseMovePoint);
  connect(ui->graphicsView, &MGraphicsView::mouseClicked,
          this, &MainWindow::on_mouseClicked);

  initGraphics();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_mouseMovePoint(QPoint point) {
  labViewCord->setText(QString::asprintf("View 坐标 (%d, %d)",
                                         point.x(),
                                         point.y()));

  auto point_scene = ui->graphicsView->mapToScene(point);
  labSceneCord->setText(QString::asprintf("Scene 坐标 (%.0f, %.0f)",
                                          point_scene.x(),
                                          point_scene.y()));
}

void MainWindow::on_mouseClicked(QPoint point) {
  QPointF point_f = ui->graphicsView->mapToScene(point);
  QGraphicsItem *item = scene->itemAt(point_f, ui->graphicsView->transform());
  if (item) {
    auto pointItem = item->mapFromScene(point);
    labItemCord->setText(QString::asprintf("Item 坐标 (%.0f, %.0f)",
                                            pointItem.x(),
                                            pointItem.y()));
  }
}

void MainWindow::initGraphics() {
  // 逻辑坐标
  QRectF rect(-200, -100, 400, 200);
  scene = new QGraphicsScene(rect);
  ui->graphicsView->setScene(scene);
  // 设置画笔
  QPen pen;
  pen.setWidth(2);

  // 画 长方形
  auto item_rect = new QGraphicsRectItem(rect);
  item_rect->setFlags(QGraphicsItem::ItemIsSelectable |
                      QGraphicsItem::ItemIsFocusable);
  item_rect->setPen(pen);
  scene->addItem(item_rect);

  // 画 椭圆
  auto item_ellipse = new QGraphicsEllipseItem(-100, -50, 200, 100);
  item_ellipse->setFlags(QGraphicsItem::ItemIsSelectable |
                         QGraphicsItem::ItemIsFocusable |
                         QGraphicsItem::ItemIsMovable);
  item_ellipse->setPos(0, 0);
  item_ellipse->setBrush(QBrush(Qt::yellow));
  item_ellipse->setPen(pen);
  scene->addItem(item_ellipse);

  // 画 圆
  auto item_ellipse2 = new QGraphicsEllipseItem(-50, -50, 100, 100);
  item_ellipse2->setFlags(QGraphicsItem::ItemIsSelectable |
                         QGraphicsItem::ItemIsFocusable |
                         QGraphicsItem::ItemIsMovable);
  item_ellipse2->setPos(rect.bottomRight());
  item_ellipse2->setBrush(QBrush(Qt::blue));
  item_ellipse2->setPen(pen);
  scene->addItem(item_ellipse2);

  scene->clearSelection();
}

void MainWindow::resizeEvent(QResizeEvent *event) {

  QRectF rectF=ui->graphicsView->sceneRect();
  ui->labViewSize->setText(
      QString::asprintf("宽度: %d, 高度: %d \n %.0f %.0f %.0f %.0f",
                        ui->graphicsView->width(),
                        ui->graphicsView->height(),
                        rectF.left(), rectF.top(),
                        rectF.width(), rectF.height()
                        ));
  QWidget::resizeEvent(event);
}
