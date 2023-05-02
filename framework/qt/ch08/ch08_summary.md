# 1. 绘图基本操作
## 1.1 相关类介绍
- QPainter 提供基础的绘图接口, 可以设置 QPen, QBrush, QFont 等绘图属性对象
- QPaintDevice 抽象父类, 提供二维绘图界面, 所有可绘图控件需要继承此类
- QPaintEngine 对不同设备抽象绘图接口, 提供给 QPaintEngine 和 QPainter 
- QPalette 使用

## 1.2 基本使用方法
### 继承控件的 paintEvent 事件
```c++
// Widget 继承 QPaintDevice 需要重载 paintEvent 函数
void PainterWidget::paintEvent(QPaintEvent *event) {
   // ...  
}
```

### QPainter 初始化
```c++
// 初始化 QPainter, 指定 widget 为 QPaintDevice
QPainter painter(this);            // 采用 widget 的物理坐标系
// 等价于
QPainter painter;
painter.begin();                   // 开始绘制
assert(true, paitner.isActive());  // painter 处于启用状态
paitner.end();                     // 一般不需要手动调用, 析构自动调用
```

### QPainter 相关设置
```c++
// 设定渲染模式
painter.setRenderHint(QPainter::Antialiasing);
painter.setRenderHint(QPainter::TextAntialiasing);

// 设定画笔
QPen pen;
pen.setWidth(10);                // 宽度
pen.setColor(Qt::red);           // 颜色样式
pen.setStyle(Qt::SolidLine);     // 实线样式
pen.setCapStyle(Qt::FlatCap);    // 终端样式
pen.setJoinStyle(Qt::BevelJoin); // 交点样式
painter.setPen(pen);

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

// 设定字体
QFont font;
font.setPointSize(30);
painter.setFont(font);
```

### QPainter 绘画接口
```c++
// 画矩形
auto width = QPaintDevice::width();
auto height = QPaintDevice::width();
QRect rec(width/4, height/4, width/2, height/2);
painter.drawRect(rec);

// 画图像
QImage q_image(":/images/image/qt.jpg");
painter.drawImage(rec, q_image);

// 画字体
painter.drawText(rec, "font");

// 画线段
QPoint points[]{QPoint(width / 2, height / 2), QPoint(width / 2, height / 3),
              QPoint(width / 3, height / 3),};
painter.drawPolygon(points, 3);  // 不连成线
painter.drawPolyline(points, 3); // 连成线
```

# 2. 坐标变化
## 2.1 五角星的点坐标
```c++
// 半径
qreal r = 100;
// 360 / 5 = 72度
qreal radian = M_PI * 72 / 180;
QPointF point_fs[]{
  QPointF(r * qCos(0 * radian), r * -qSin(0 * radian)),
  QPointF(r * qCos(1 * radian), r * -qSin(1 * radian)),
  QPointF(r * qCos(2 * radian), r * -qSin(2 * radian)),
  QPointF(r * qCos(3 * radian), r * -qSin(3 * radian)),
  QPointF(r * qCos(4 * radian), r * -qSin(4 * radian)),
};
```

## 2.2 QPainterPath 使用
```c++
// 画五角星的路径
QPainterPath path;
path.moveTo(point_fs[0]);  // 起点
path.lineTo(point_fs[2]);  // 每隔一个点连一次线
path.lineTo(point_fs[4]);
path.lineTo(point_fs[1]);
path.lineTo(point_fs[3]);
path.lineTo(point_fs[0]);
path.closeSubpath();       // 关闭子路径, 重新一个新起点(0, 0)

path.addText(point_fs[0], font, "1");
path.addText(point_fs[1], font, "2");
path.addText(point_fs[2], font, "3");
path.addText(point_fs[3], font, "4");
path.addText(point_fs[4], font, "5");
```

## 2.3 坐标变化
```c++
// 水平平移
painter.translate(100, 120);  
painter.drawPath(path);
// 顺时针旋转 90 度
painter.rotate(90);
// x轴 和 y轴 放大缩小 
painter.scale(1.2, 1.2);
```

## 2.4 QPainterPath 状态栈
```c++
// 保留 painter 状态
painter.save();

// ...

// 恢复 painter 状态, 重置坐标系状态
painter.restore();
painter.resetTransform();
painter.save();

// ...

painter.restore();
painter.resetTransform();
painter.save();

// ...

painter.restore();
painter.resetTransform();
```

# 3. 视口与窗口
## 3.1 相关类介绍
- 视口, 设备物理区域的一个范围, 也是 painter 绘图范围(软性的), 默认为整个范围
- 窗口, 对应视口区域, 采用逻辑坐标系, 是对物理区域的抽象

## 3.2 视口与窗口的使用
```c++
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
```

# 4. GraphicsView 基础
## 4.1 相关类
- GraphicsScene 场景类, 抽象类, 管理图形项, 传递事件
- GraphicsView 视图类, 显示场景中的内容, 转换事件给场景类
- GraphicsItem 图形项, 支持各类事件, 可以组合

## 4.2 坐标
### 图形项坐标
- 中心为原点 
- 事件坐标会被自动转换为自身坐标系
- boundingRect() 返回的是自身坐标
- pos() 返回父项中的坐标
- scenePos() 返回 scene 内的坐标

### 视图坐标
- 与物理坐标一致
- 事件先由视图坐标确定, 然后一步一步传递给场景, 图形项

### 场景坐标
- 中心为原点, 也可以定义坐标范围为某一象限
- sceneRect() 获取场景区域
- 图形项的 sceneBoundingRect() 返回场景坐标
- 图形项的 BoundingRect 改变 会触发场景的 changed() 事件

## 4.3 显示坐标的列子
### 继承 GraphicsView
```c++
// 使得 view 拥有鼠标相关事件, 需要覆盖相关函数
// 需要在 ui 设计界面将 QGraphicsView 控件提升到自定义类的头文件中 
class MGraphicsView : public QGraphicsView {
  
Q_OBJECT

 public:
  explicit MGraphicsView(QWidget *parent = nullptr);
  ~MGraphicsView() override;
 signals:
  void mouseMovePoint(QPoint point);                 // 鼠标移动信号
  void mouseClicked(QPoint point);                   // 鼠标点击信号
 protected:
  void mousePressEvent(QMouseEvent *event) override; // 鼠标按触事件
  void mouseMoveEvent(QMouseEvent *event) override;  // 鼠标移动事件
 private:
  Ui::MGraphicsView *ui;
  QLabel *labViewCord;
  QLabel *labSceneCord;
  QLabel *labItemCord;
  QLabel *labItemInfo;
  QGraphicsScene *scene;
};
```

### View 相应事件
- 将 View 的事件传递给 MainWindow
```c++
// override 鼠标左击事件
void MGraphicsView::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    // 获取位置地点
    QPoint point = event->pos();
    // 发送 mouseClicked signal 给 MainWindow 处理
    emit mouseClicked(point);
  }
  // 一定要调用父类的虚方法
  QGraphicsView::mousePressEvent(event);
}
// override 鼠标移动事件
void MGraphicsView::mouseMoveEvent(QMouseEvent *event) {
  auto point = event->pos();
  // 发送 mouseMovePoint signal 给 MainWindow 处理
  emit mouseMovePoint(point);
  QGraphicsView::mouseMoveEvent(event);
}
```

### View 事件的槽函数
```c++
// 显示 scene 坐标 和 view 坐标
void MainWindow::on_mouseMovePoint(QPoint point) {
  labViewCord->setText(QString::asprintf("View 坐标 (%d, %d)",
                                         point.x(), point.y()));
  auto point_scene = ui->graphicsView->mapToScene(point);
  labSceneCord->setText(QString::asprintf("Scene 坐标 (%.0f, %.0f)",
                                          point_scene.x(), point_scene.y()));
}

// 显示 item 坐标
void MainWindow::on_mouseClicked(QPoint point) {
  // 获取 scene 坐标
  QPointF point_f = ui->graphicsView->mapToScene(point);
  // 获取 view 的 变化矩阵
  QTransform transform = ui->graphicsView->transform();
  // 获取 item 对象
  QGraphicsItem *item = scene->itemAt(point_f, transform); // 必须提供矩阵
  if (item) {
    auto pointItem = item->mapFromScene(point);
    labItemCord->setText(QString::asprintf("Item 坐标 (%.0f, %.0f)",
                                           pointItem.x(), pointItem.y()));
  }
}
```

### View 相关设置
```c++
// 启用鼠标跟踪, 在鼠标移动过程中, 会实时接收到 QMouseEvent 事件
graphicsView->setMouseTracking(true);
// 设定鼠标样式
graphicsView->setCursor(Qt::CrossCursor);
// 设定为橡皮筋模式, 框选内容
graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
```

### Item 添加
```c++
// 添加 Item 的坐标系是以 scene 为准
auto item_ellipse = new QGraphicsEllipseItem(-100, -50, 200, 100);
// Item 相关设置
item_ellipse->setFlags(QGraphicsItem::ItemIsSelectable |
                       QGraphicsItem::ItemIsFocusable |
                       QGraphicsItem::ItemIsMovable);
```

# 5. GraphicsView 实例
## 5.1 双击 Dialog
```c++
// 字体 Dialog
template<typename T>
void MainWindow::setFontColor(T *item) {
  auto font = item->font();
  bool ok;
  font = QFontDialog::getFont(&ok, font, this, "请选择字体类型");
  if (ok) {
    item->setFont(QFont(font));
  }
}

// 设定相关图形项属性
auto point_scene = ui->gView->mapToScene(point);
auto item = scene->itemAt(point_scene, ui->gView->transform());
if (!item) return;
switch (item->type()) {
  case QGraphicsRectItem::Type: {
  auto item_rect = dynamic_cast<QGraphicsRectItem *>(item);
  setBrushColor(item_rect);
  break;
}
// ...
```

## 5.2 组合打散
```c++
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
```

## 5.3 变形恢复
```c++
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
```