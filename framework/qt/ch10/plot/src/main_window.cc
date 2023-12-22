#include "../header/main_window.h"
#include "../header/m_graphics_view.h"
#include "ui_main_window.h"

#include <QGraphicsScene>
#include <QLabel>
#include <QKeyEvent>
#include <QGraphicsEllipseItem>
#include <QTime>
#include <QInputDialog>
#include <QFont>
#include <QColorDialog>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  labItemInfo = new QLabel("item info: ");
  labItemInfo->setMinimumWidth(150);
  ui->statusbar->addWidget(labItemInfo);

  scene = new QGraphicsScene(-300, -200, 600, 200);
  ui->gView->setScene(scene);
  ui->gView->setCursor(Qt::CrossCursor);
  ui->gView->setMouseTracking(true);
  ui->gView->setDragMode(QGraphicsView::RubberBandDrag);

  qsrand(QTime::currentTime().second());

  connect(ui->gView, &MGraphicsView::mouseMovePoint,
          this, &MainWindow::on_mouseMovePoint);
  connect(ui->gView, &MGraphicsView::mouseClicked,
          this, &MainWindow::on_mouseClicked);
  connect(ui->gView, &MGraphicsView::mouseDoubleClick,
          this, &MainWindow::on_mouseDoubleClick);
  connect(ui->gView, &MGraphicsView::keyPress,
          this, &MainWindow::on_keyPress);

  setGeometry(100, 100, 1000, 600);
  setMinimumSize(200, 200);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_mouseMovePoint(QPoint point) {

}

void MainWindow::on_mouseClicked(QPoint point) {
  auto point_scene = ui->gView->mapToScene(point);
  auto item = scene->itemAt(point_scene, ui->gView->transform());
  if (item) {
    auto item_point = item->scenePos();
    labItemInfo->setText("Item Info:" + item->data(kItemDesc).toString() +
        ", ID: " + item->data(kItemId).toString() +
        ", Item Pos: " + QString::asprintf("(%.0f, %.0f) ", item_point.x(), item_point.y())
    );
  }
}

void MainWindow::on_mouseDoubleClick(QPoint point) {
  auto point_scene = ui->gView->mapToScene(point);
  auto item = scene->itemAt(point_scene, ui->gView->transform());
  if (!item) return;
  switch (item->type()) {
    case QGraphicsRectItem::Type: {
      auto item_rect = dynamic_cast<QGraphicsRectItem *>(item);
      setBrushColor(item_rect);
      break;
    }
    case QGraphicsEllipseItem::Type: {
      auto item_ellipse = dynamic_cast<QGraphicsEllipseItem *>(item);
      setBrushColor(item_ellipse);
      break;
    }
    case QGraphicsPolygonItem::Type: {
      auto item_polygon = dynamic_cast< QGraphicsPolygonItem *>(item);
      setBrushColor(item_polygon);
      break;
    }
    case QGraphicsLineItem::Type: {
      auto item_line= dynamic_cast<QGraphicsLineItem *>(item);
      setPenColor(item_line);
      break;
    }
    case QGraphicsTextItem::Type: {
      auto item_text= dynamic_cast< QGraphicsTextItem *>(item);
      setFontColor(item_text);
      break;
    }
    default:
      ;
  }
}

void MainWindow::on_keyPress(QKeyEvent *event) {
  auto items = scene->selectedItems();
  auto cnt = items.count();
  if (cnt == 0) return;

  auto target_item = items.at(0);

  if (event->key() == Qt::Key_Delete) {
    scene->removeItem(target_item);
  } else if (event->key() == Qt::Key_PageUp) {
  } else if (event->key() == Qt::Key_PageDown) {
  } else if (event->key() == Qt::Key_Left) {
    target_item->setX(-1 + target_item->x());
  } else if (event->key() == Qt::Key_Right) {
    target_item->setX( 1 + target_item->x());
  } else if (event->key() == Qt::Key_Down) {
    target_item->setY( 1 + target_item->y());
  } else if (event->key() == Qt::Key_Up) {
    target_item->setY(-1 + target_item->y());
  }

}

void MainWindow::on_actItem_Rect_triggered() {
  auto item = new QGraphicsRectItem(-50, -30, 100, 60);
  item->setFlags(QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsFocusable |
                 QGraphicsItem::ItemIsMovable);
  item->setBrush(QBrush(Qt::blue));
  item->setZValue(++frontZ);
  item->setPos(-50 + qrand() % 100, -50 + qrand() % 100);
  item->setData(kItemId, ++seqNum);
  item->setData(kItemDesc, "矩形");

  scene->addItem(item);
  scene->clearSelection();
  item->setSelected(true);
}

void MainWindow::on_actItem_Ellipse_triggered() {
  auto item = new QGraphicsEllipseItem(-50, -50, 200, 100);
  item->setFlags(QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsFocusable |
                 QGraphicsItem::ItemIsMovable);
  item->setBrush(QBrush(Qt::yellow));
  item->setZValue(++frontZ);
  item->setPos(-50 + qrand() % 100, -50 + qrand() % 100);
  item->setData(kItemId, ++seqNum);
  item->setData(kItemDesc, "椭圆");

  scene->addItem(item);
  scene->clearSelection();
  item->setSelected(true);
}

void MainWindow::on_actItem_Circle_triggered() {
  auto item = new QGraphicsEllipseItem(-50, -50, 100, 100);
  item->setFlags(QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsFocusable |
                 QGraphicsItem::ItemIsMovable);
  item->setBrush(QBrush(Qt::yellow));
  item->setZValue(++frontZ);
  item->setPos(-50 + qrand() % 100, -50 + qrand() % 100);
  item->setData(kItemId, ++seqNum);
  item->setData(kItemDesc, "圆形");

  scene->addItem(item);
  scene->clearSelection();
  item->setSelected(true);
}

void MainWindow::on_actItem_Line_triggered() {
  auto item = new QGraphicsLineItem(-50, -50, 100, -50);
  item->setFlags(QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsFocusable |
                 QGraphicsItem::ItemIsMovable);
  QPen pen;
  pen.setWidth(10);
  pen.setColor(Qt::black);
  item->setPen(pen);

  item->setZValue(++frontZ);
  item->setPos(-50 + qrand() % 100, -50 + qrand() % 100);
  item->setData(kItemId, ++seqNum);
  item->setData(kItemDesc, "直线");

  scene->addItem(item);
  scene->clearSelection();
  item->setSelected(true);
}

void MainWindow::on_actItem_Polygon_triggered() {
  auto item = new QGraphicsPolygonItem;
  item->setFlags(QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsFocusable |
                 QGraphicsItem::ItemIsMovable);
  QPolygon polygon;
  polygon.append({-20, -20});
  polygon.append({ 20, -20});
  polygon.append({ 40,  40});
  polygon.append({-40,  40});
  item->setPolygon(polygon);

  item->setBrush(QBrush(Qt::yellow));
  item->setZValue(++frontZ);
  item->setPos(-50 + qrand() % 100, -50 + qrand() % 100);
  item->setData(kItemId, ++seqNum);
  item->setData(kItemDesc, "多边形");

  scene->addItem(item);
  scene->clearSelection();
  item->setSelected(true);
}

void MainWindow::on_actItem_Triangle_triggered() {
  auto item = new QGraphicsPolygonItem;
  item->setFlags(QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsFocusable |
                 QGraphicsItem::ItemIsMovable);
  QPolygon polygon;
  polygon.append({-20, -20});
  polygon.append({ 20, -20});
  polygon.append({  0,   0});
  item->setPolygon(polygon);

  item->setBrush(QBrush(Qt::yellow));
  item->setZValue(++frontZ);
  item->setPos(-50 + qrand() % 100, -50 + qrand() % 100);
  item->setData(kItemId, ++seqNum);
  item->setData(kItemDesc, "三角形");

  scene->addItem(item);
  scene->clearSelection();
  item->setSelected(true);
}

void MainWindow::on_actItem_Text_triggered() {
  auto str = QInputDialog::getText(this, "输入对话框", "请输入:");
  auto item = new QGraphicsTextItem(str);
  item->setFlags(QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsFocusable |
                 QGraphicsItem::ItemIsMovable);

  QFont font;
  font.setPointSize(20);
  item->setDefaultTextColor(Qt::black);
  item->setFont(font);

  item->setZValue(++frontZ);
  item->setPos(-50 + qrand() % 100, -50 + qrand() % 100);
  item->setData(kItemId, ++seqNum);
  item->setData(kItemDesc, "三角形");

  scene->addItem(item);
  scene->clearSelection();
  item->setSelected(true);
}

void MainWindow::on_actZoomIn_triggered() {
  auto list = scene->selectedItems();
  auto cnt = list.count();
  if (cnt != 0) {
    for (int i = 0; i < cnt; ++i) {
      auto item = list.at(i);
      item->setScale(0.1 + item->scale());
    }
  } else {
    ui->gView->scale(1.1, 1.1);
  }
}

void MainWindow::on_actZoomOut_triggered() {
  auto list = scene->selectedItems();
  auto cnt = list.count();
  if (cnt != 0) {
    for (int i = 0; i < cnt; ++i) {
      auto item = list.at(i);
      item->setScale(-0.1 + item->scale());
    }
  } else {
    ui->gView->scale(0.9, 0.9);
  }
}

void MainWindow::on_actRestore_triggered() {
  auto list = scene->selectedItems();
  auto cnt = list.count();
  if (cnt != 0) {
    for (int i = 0; i < cnt; ++i) {
      auto item = list.at(i);
      item->setScale(1);
    }
  } else {
    ui->gView->resetTransform();
  }
}

void MainWindow::on_actRotateLeft_triggered() {
  auto list = scene->selectedItems();
  auto cnt = list.count();
  if (cnt != 0) {
    for (int i = 0; i < cnt; ++i) {
      auto item = list.at(i);
      item->setRotation(-90 + item->rotation());
    }
  } else {
    ui->gView->rotate(-90);
  }
}

void MainWindow::on_actRotateRight_triggered() {
  auto list = scene->selectedItems();
  auto cnt = list.count();
  if (cnt != 0) {
    for (int i = 0; i < cnt; ++i) {
      auto item = list.at(i);
      item->setRotation(90 + item->rotation());
    }
  } else {
    ui->gView->rotate(90);
  }
}

void MainWindow::on_actEdit_Front_triggered() {
  auto list = scene->selectedItems();
  auto cnt = list.count();
  if (cnt != 0) {
    for (int i = 0; i < cnt; ++i) {
      auto item = list.at(i);
      item->setZValue(++frontZ);
    }
  }
}

void MainWindow::on_actEdit_Back_triggered() {
  auto list = scene->selectedItems();
  auto cnt = list.count();
  if (cnt != 0) {
    for (int i = 0; i < cnt; ++i) {
      auto item = list.at(i);
      item->setZValue(--backZ);
    }
  }
}

void MainWindow::on_actGroup_triggered() {
  auto list = scene->selectedItems();
  auto cnt = list.count();
  if (cnt == 0) return;

  auto group = new QGraphicsItemGroup;
  scene->addItem(group);
  for (int i = 0; i < cnt; ++i) {
    auto item = list.at(i);
    item->setSelected(false);
    item->clearFocus();
    group->addToGroup(item);
  }
  group->setFlags(QGraphicsItem::ItemIsSelectable |
                  QGraphicsItem::ItemIsFocusable |
                  QGraphicsItem::ItemIsMovable);
  group->setZValue(++frontZ);
  scene->clearSelection();
  group->setSelected(true);
}

void MainWindow::on_actGroupBreak_triggered() {
  auto list = scene->selectedItems();
  auto cnt = list.count();
  if (cnt == 0) return;

  QList<QGraphicsItemGroup *> groups;
  for (int i = 0; i < cnt; ++i) {
    auto item = list.at(i);
    if (item->type() == QGraphicsItemGroup::Type) {
      groups.append(dynamic_cast<QGraphicsItemGroup *>(item));
    }
  }

  for (auto item : groups) {
    scene->destroyItemGroup(item);
  }
}

void MainWindow::on_actEdit_Delete_triggered() {
  auto list = scene->selectedItems();
  auto cnt = list.count();
  if (cnt == 0) return;

  for (auto item : list) {
    scene->removeItem(item);
  }
}

template<typename T>
void MainWindow::setPenColor(T *item) {
  auto pen = item->pen();
  auto color = pen.color();
  color = QColorDialog::getColor(color, nullptr, "请选择绘笔颜色");
  if (color.isValid()) {
    pen.setColor(color);
    item->setPen(pen);
  }
}

template<typename T>
void MainWindow::setFontColor(T *item) {
  auto font = item->font();
  bool ok;
  font = QFontDialog::getFont(&ok, font, this, "请选择字体类型");
  if (ok) {
    item->setFont(QFont(font));
  }
}

template<typename T>
void MainWindow::setBrushColor(T *item) {
  auto color = item->brush().color();
  color = QColorDialog::getColor(color, nullptr, "请选择填充颜色");
  if (color.isValid()) {
    item->setBrush(QBrush(color));
  }
}