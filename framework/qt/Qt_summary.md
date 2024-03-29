# 1. 认识 Qt
## 安装配置
- 网址: https://download.qt.io/official_releases/online_installers/qt-unified-windows-x64-online.exe.mirrorlist
- Clion Tool Set: qt\Tools\mingw530_32
- Clion External Tool: qt\5.9.9\mingw53_32\bin\designer.exe  $FileDir$ $FileName$

## 项目模板
- Widget Application: Widget-UI 项目
- Console Application: 控制台 项目
- Quick Application: QML-UI 项目

## 三种基类
- QMainWindow 主窗口类
- QWidget 可视界面类
- QDialog 对话窗口类

## 项目结构
- build 构建目录
- header 头文件
- src 源文件
- ui ui文件
- main.cc 主程序入口
- CMakeList.txt CMake文件 

## CMake 文件
```cmake
cmake_minimum_required(VERSION 3.5)

project(hello_qt LANGUAGES CXX)

# 设置语言标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 加入 build 与 project 目录 到 include 路径中
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置自定义 Qt 安装路径 /mingw53_32
set(CUSTOM_QT_INSTALL_PATH "D:/DevelopTool/qt/5.9.9")
# 指定 UIC 路径
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

set(CMAKE_AUTOMOC ON) # 自动采用 MOC 处理源文件
set(CMAKE_AUTOUIC ON) # 自动采用 UIC 处理.ui文件
set(CMAKE_AUTORCC ON) # 自动采用 RCC 处理.qrc文件

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)  # 引用 Qt 模块

# 主界面
add_library(main_window SHARED
            src/mainwindow.cc
            header/mainwindow.h) # MOC 原因需要包含头文件
target_link_libraries(main_window PUBLIC Qt5::Widgets) # 引用 Qt 库
target_include_directories(main_window PUBLIC header)  # 指定 头文件夹

# 主程序
add_executable(hello_qt main.cc)
target_link_libraries(hello_qt PRIVATE main_window)
```

## QtDesign 使用

# 2. GUI 应用程序设计基础
## 2.1 UI文件设计与运行机制
- 对象浏览器中的继承关系 举例: QObject->QWidget->QFrame->QLabel
- 信号槽机制: sender->signal->receiver->slot
- main 函数
```c++
#include "widget.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // 创建应用程序
    Widget w;                    // 定义窗口并显示
    w.show();
    return a.exec();             // 应用程序开始消息循环和事件处理
}
```

- UI 可视化生成类的关系
```c++
// Widget.h
namespace Ui { class Widget; }   // UI 可视化生成的类
class Widget : public QWidget {  // 公有继承 QWidget 来实现 Qt 的公有特性
    Q_OBJECT                     // 实现信号槽机制的宏, 必须是 private
public:
    Widget(QWidget *parent = nullptr);  // 默认容器类为 nullptr
    ~Widget();
private:
    Ui::Widget *ui;              // 指向可视化生成的对象, 实现解耦目的
};
// Widget.cpp
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
}
Widget::~Widget() {
    delete ui;
}


// ui_widget.h 可视化生成的类
class Ui_Widget {
public:
    QLabel *labDemo;
    QPushButton *bntClose;

    // 初始化各个控件, 链接信号槽
    void setupUi(QWidget *Widget) {
        // ...
        retranslateUi(Widget);
        QObject::connect(bntClose, SIGNAL(clicked()), Widget, SLOT(close()));
        QMetaObject::connectSlotsByName(Widget);
    } 
    // 翻译部分字符串
    void retranslateUi(QWidget *Widget) {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        labDemo->setText(QApplication::translate("Widget", "Hello!Widget!", Q_NULLPTR));
        bntClose->setText(QApplication::translate("Widget", "Close", Q_NULLPTR));
    } 

};

namespace Ui {
// Ui::Widget 即是Ui_Widget
    class Widget: public Ui_Widget {};
}
```

## 2.2 可视化ui设计
- 组件的 objectName, 容器类, 布局管理
- buddy 关系, tab 顺序
- 信号槽相关函数
  - QObject::connect(sender, SIGNAL(clicked()), receiver, SLOT(close()));
  - QMetaObject::connectSlotsByName(XXXWidget);
  - 通过名称连接的格式`void on_<object_name>_<signal_name>(<signal_param>)`
- 信号槽注意事项:
  - 按连接顺序依次立即执行, 执行后才会继续执行激发信号后的代码
  - 多信号可连接同一个槽函数
  - 要加入 Q\_OBJECT 宏, 连接时信号和槽的参数要对应一致

## 2.3 代码化ui设计
```c++
// 初始化 UI
void Dialog::iniUI()
{
    // 控件对象
    chkBoxUnder = new QCheckBox(tr("Underline"));
    // ...
    // 布局对象
    QHBoxLayout *HLay1 = new QHBoxLayout;
    HLay1->addWidget(chkBoxUnder);
    // ...
    btnOK = new QPushButton(tr("OK"));
    btnCancel= new QPushButton(tr("Cancel"));
    btnClose= new QPushButton(tr("Close"));
    QHBoxLayout *HLay3 = new QHBoxLayout;
    // 注意加入顺序
    HLay3->addStretch();
    HLay3->addWidget(btnOK);
    HLay3->addWidget(btnCancel);
    HLay3->addStretch();
    HLay3->addWidget(btnClose);
    // ...
    // 布局嵌套布局
    QVBoxLayout *VLay = new QVBoxLayout;
    VLay->addLayout(HLay1);
    VLay->addLayout(HLay2);
    VLay->addWidget(txtEdit);
    VLay->addLayout(HLay3);
    setLayout(VLay);
}
// 连接信号槽
void Dialog::iniSignalSlots()
{
    connect(rBtnBlack, SIGNAL(clicked()), this, SLOT(setTextFontColour()));
    // ...
    connect(chkBoxUnder, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxUnder(bool)));
    // ...
    connect(btnOK, SIGNAL(clicked()), this, SLOT(accept()));
    // ...
    QMetaObject::connectSlotsByName(this);
}
```

## 2.4 混合设计
- 创建并添加资源
```xml
<!--> xxx.qrc 格式 <!-->
<RCC>
    <qresource prefix="/images">
        <file>path/to/file</file>
    </qresource>
</RCC>

<!--> 在 cmake 中 添加 resource.qrc 到 exe <!-->
```

- 通过代码将控件添加状态栏和工具栏
```c++
fLabCurFile = new QLabel;
fLabCurFile->setMinimumWidth(150);
fLabCurFile->setText(tr("当前文件: "));
// 添加进 statusbar 中
ui->statusbar->addWidget(fLabCurFile);
```

- 菜单栏中的 action 关于文字修改的槽函数实现
```c++
// triggered() 信号调用 QTextEdit 的四个槽函数
paste();
cut();
copy();
clear();

void QTextEdit::copyAvailable(bool yes);  // 根据是否选中文字发送信号
void QTextEdit::selectionChanged();       // 根据选中文字变化发送信号

// 改变选中文字的字体
QTextCharFormat fmt;
fmt.setFontItalic(checked);
ui->txtEdit->mergeCurrentCharFormat(fmt);
```

- 添加应用程序图标
```c++
QIcon icon(":/images/image/aim.ico");  // 格式 :/prefix/path/to/file
widget.setWindowIcon(icon);
```

# 3 Qt 类库
## 3.1 核心特点
- Meta-Object Compiler 提供元对象系统, 每个类需继承 QObject 类并添加 Q\_OBJECT 宏
- 元对象系统实现了信号槽, 动态属性, 动态类型转换等功能
```c++
// QObject 基类中含有关于对象关系的函数, 有的需通过 QMetaObject 指针获取相关信息
QObject *obj = new QPushButton;  
const QMetaObject *meta = obj->metaObject();  // // 通过 metaObject() 返回 QMetaObject 指针
String str = meta->className();  // 返回类名

// 是否继承所给的类
bool QObject::inherits(const char *className) const 

// 等价 dynamic_cast, 出错返回 nullptr
QPushButton *derived = qobject_cast<QPushButton *>(obj);
```

- 属性系统: Q\_PROPERTY宏, Q\_CLASSINFO
```c++
// Q_PROPERTY 宏设定属性, 访问属性
 Q_PROPERTY(
  unsigned age  // type name 
  READ age      // age() 为读函数, 需实现
  WRITE setAge  // setAge() 为写函数, 需实现
  NOTIFY ageChanged // ageChange(...) 为信号函数, 不用实现, setAge() 会激发信号, 其他函数则不会
)

Q_PROPERTY(
  QString name 
  MEMBER m_name  // 直接与数据成员关联, 通过
)

// 通过 setProperty("key_name", value) 和 property("key_name") 访问属性
// 如果 setProperty 键值不存在则会定义一个新的动态属性
girl->setProperty("score", 81);
QString sex = aPerson->property("sex").toString();  // QVariant => QString


// Q_CLASSINFO 宏提供额外信息, 键值必须都是字符串
Q_CLASSINFO("author", "san")
Q_CLASSINFO("company", "xxx")
Q_CLASSINFO("version", "1.0.0")

QMetaClassInfo classInfo = meta->classInfo(index);
classInfo.name();  // 获取名称
classInfo.value(); // 获取键值
```

- 两种信号槽的链接方式, sender 获取发射者元对象 
```c++
// 第一种链接, 通过 SIGNAL 和 SLOT 宏生成字符串
QMetaObject::Connection QObject::connect(const QObject *sender, 
                                         const char *signal, 
                                         const QObject *receiver, 
                                         const char *method, 
                                         Qt::ConnectionType type = Qt::AutoConnection)
connect(scrollBar, SIGNAL(valueChanged(int)),
        label,  SLOT(setNum(int)));

// 第二种链接, 通过 函数指针, 要求信号函数没有重载
QMetaObject::Connection QObject::connect(const QObject *sender, 
                                         const QMetaMethod &signal, 
                                         const QObject *receiver, 
                                         const QMetaMethod &method, 
                                         Qt::ConnectionType type = Qt::AutoConnection)
connect(scrollBar, &ScrollBar::valueChanged,
        label,  &Label::setNum);

// 四种链接模式
Qt::AutoConnection // 发送者和接收者是否同线程选择后两种方式
Qt::DirectConnection // 信号发射, 槽函数立即执行, 发送者和接收者同线程
Qt::QueuedConnection // 事件循环到接收者后执行槽函数, 发送者和接收者不同线程
Qt::BlockingQueuedConnection // 信号线程阻塞直到槽函数完成, 发送者和接收者不能同线程否则死锁
  
auto p = qobject_cast<QPerson>(sender()); // 通过 sender() 获取信号发射者元对象
```

- 自定义信号, 触发信号
```c++
// 定义信号, 不用实现
signals:
    void ageChanged(unsigned value);
    
// emit 触发信号
void QPerson::incAge()
{
    ++m_age;
    emit(ageChanged(m_age));
}
```

- 元对象使用例子
```c++
const auto *meta = boy->metaObject();  // 获取元对象
// 使用 property
for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
  QMetaProperty prop = meta->property(i);  // 通过 meta 的下标获取属性
  const auto *propName = prop.name();  // 获取属性的名字
  auto propValue = boy->property(propName).toString();  // 通过属性名字获取属性值
}
// 使用 classinfo
for (int i = meta->classInfoOffset(); i< meta->classInfoCount(); ++i) {
  QMetaClassInfo classInfo = meta->classInfo(i);
  ui->txtEdit->appendPlainText(
    QString("Name = %1, Value = %2").arg(classInfo.name()).arg(classInfo.value()));
}
```

## 3.2 全局定义
- Qt 的数据类型
- 基本函数
- QT\_VERSION, Q\_BYTE\_ORDER,  Q\_UNUSED, forever, qDebug

## 3.3 容器
- QList 数组列表, 前后增删快, 下标索引访问 QVector 动态数组, 下标索引访问, 访问效率更高
- QLinkedList 链表
- QStack, QQueue
- QSet, QMap 键顺序, QHash 不顺序
- QMultiMap, QMultiHash 键值访问返回 QList

## 3.4 容器迭代
- Java 类型迭代, 指向元素中间, 操作上一个数据项
- STL 类型迭代, 类指针
- 隐式共享, 只有在数据项变动时才实质复制, 注意访问时出现操作不同对象的迭代器的问题

# 4. 常用控件
## 4.1 字符串转换
- 字符串转数值
  - toInt(nullptr, base) 指针指向 bool
  - toDouble(nullptr)
- 数值转字符串 
  - QString::number(value, 'f', base) / str.setNum(value, 'f', base)
  - QString::asprintf("%", value) / str.sprintf("%", value) 
- 字符串常用函数
```c++
append(); prepend();       // 追加
toUpper(); toLower();      // 转化大小写
count(); size(); length(); // 字符个数
trimmed(); simplified();   // 头尾去空格 和 中间去空格
isNull(); isEmpty("");     // 未赋值为 null, "\0"为 empty
indexOf(); lastIndexOf();  // 返回 str 字符下标


// 以 sep 为分隔符, 提取从下标为 start 到 end 段的字符串
QString QString::section(QChar sep, int start, int end = -1, SectionFlags flags = SectionDefault) const
```

## 4.2 QSpinBox与QDoubleSpinBox
- setValue() 设置数值
- value() 获取数值

## 4.3数值显示输入控件
- QSlider
- QScrollBar
- QProgressBar
- QDial
- QLCDNumber
```c++
// 设置画盘颜色
void Widget::on_SliderRed_valueChanged(int value) {
  Q_UNUSED(value);
  auto R = ui->SliderRed->value();
  auto G = ui->SliderGreen->value();
  auto B = ui->SliderBlue->value();
  auto alpha = ui->SliderAlpha->value();
  QColor color(R, G, B, alpha);
  auto pal = ui->textEdit->palette();
  pal.setColor(QPalette::Base, color);
  ui->textEdit->setPalette(pal);
}
```

## 4.4 日期与定时器
- QTime, QDate, QDateTime
- QTimeEdit, QDateEdit, QDateTimeEdie
- QCalendarWidget
- QTimer, 每间隔时间触发 timeout() 信号

## 4.5 QComboBox 与 QPlainTextEdit
- 添加数据键值 `comboBox2->addItem(icon, key, value);`
- QPlainTextEdit 通过 QTextDocument 类 存储文字块 QTextBlock
```c++
void Widget::on_btnToComboBox_clicked() {
  auto doc = ui->plainTextEdit->document();
  QIcon icon(":/images/image/aim.ico");
  auto num = doc->blockCount();  // 获取 block 块数
  for (int i = 0; i < num; ++i) {
    auto text = doc->findBlockByNumber(i).text();  // 遍历每行内容
    ui->comboBox->addItem(icon, text);
  }
}
```

- QPlainTextEdit 创建生成菜单栏
```c++
void Widget::on_plainTextEdit_customContextMenuRequested(const QPoint &point) {
  QMenu *p = ui->plainTextEdit->createStandardContextMenu();
  p->exec(point);
}
```

## 4.6 QListWidget 和 QToolButton
- 控件之间的关联
```c++
// QToolButton 与 QAction 关联
ui->tbtnListDelete->setDefaultAction(ui->actListDelete);

// 下拉 QToolButton 与 多个 QAction 关联
QMenu *menu = new QMenu(this);
menu->addAction(ui->actSelALL);
menu->addAction(ui->actSelNone);
menu->addAction(ui->actSelInvs);
ui->actSelPopMenu->setMenu(menu);  // 给 Action 增加 menu
ui->tBtnSelectItem->setDefaultAction(ui->actSelPopMenu);

// 增加右键菜单属性
ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

// QToolBox 与 QTabWidget 关联
void MainWindow::on_toolBox_currentChanged(int index) {
  ui->tabWidget->setCurrentIndex(index);
}
```

- listWidget 基础操作
```c++
ui->listWidget->addItem(item);
ui->listWidget->insertItem(ui->listWidget->currentRow(), item);
auto item = ui->listWidget->takeItem(row);
ui->listWidget->clear();
```

- 自定义右键菜单
```c++
void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos) {
  Q_UNUSED(pos);
  auto *menu = new QMenu(this);
  menu->addAction(ui->actListIni);
  menu->addAction(ui->actListClear);
  menu->addAction(ui->actListInsert);
  menu->addAction(ui->actListAppend);
  menu->addAction(ui->actListDelete);
  menu->addSeparator();
  menu->addAction(ui->actSelALL);
  menu->addAction(ui->actSelInvs);
  menu->addAction(ui->actSelNone);
  menu->exec(QCursor::pos());
  delete menu;
}
```

## 4.7 QTreeWidget 和 QDockWidget
- QDockWidget 布局使用
```c++
// 窗体显示移动与按钮联调
void MainWindow::on_dockWidget_visibilityChanged(bool visible) {
  ui->actDockVisible->setChecked(visible);
}
void MainWindow::on_dockWidget_topLevelChanged(bool topLevel) {
  ui->actDockFloat->setChecked(topLevel);
}
void MainWindow::on_actDockVisible_toggled(bool tog) {
  ui->dockWidget->setVisible(tog);
}
void MainWindow::on_actDockFloat_triggered(bool checked) {
  ui->dockWidget->setFloating(checked);
}
```

- QTreeWidget 基本用法
```c++
// 在 this 中央显示 FileDialog, 标题为"文件浏览", 工作目录为 "/d/"
auto dir_name = QFileDialog::getExistingDirectory(this, "文件浏览", "/d/");
// 在 this 中央显示 FileDialog, 标题为"文件浏览", 工作目录为 "/d/", 过滤只保留 Images 类文件
auto files = QFileDialog::getOpenFileNames(this, "打开多个文件", "/d/",
                                           "Images(*.png *.xpm *.jpg)");

// 1. QTreeWidgetItem 增加方法
void MainWindow::addFolderItem(QTreeWidgetItem *parItem, const QString &dir) {
  QIcon icon(":/images/image/open3.bmp");
  auto folder_name = getFinalFolderName(dir);
  auto item = new QTreeWidgetItem(itGroupItem);

  // 根据 colNum 设置 text 或 icon
  item->setIcon(colItem, icon);
  item->setText(colItem, folder_name);
  item->setText(colItemType, "type=itGroupItem");
  item->setCheckState(colItem, Qt::Checked);

  // 设置标志
  item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |
                 Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);

  // 设置数据
  item->setData(colItem, Qt::UserRole, QVariant(dir));
  if (parItem) parItem->addChild(item);
}

// 2. QTreeWidgetItem 删除方法
void MainWindow::on_actDeleteItem_triggered() {
  auto item = ui->treeWidget->currentItem();
  if (!item) return;
  auto parItem = item->parent();
  parItem->removeChild(item);
  delete item;
  ui->treeWidget->setCurrentItem(parItem);
}

// 3. QTreeWidgetItem 遍历方法
void MainWindow::on_actScanItems_triggered() {
  for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
    auto top_item = ui->treeWidget->topLevelItem(i);
    changeItemCaption(top_item);
  }
}
void MainWindow::changeItemCaption(QTreeWidgetItem *item) {
  auto str = "*" + item->text(colItem);
  item->setText(colItem, str);
  for (int i = 0; i < item->childCount(); ++i) {
    changeItemCaption(item->child(i));
  }
}
```

- ScrollArea, Pixmap 使用
```c++
void MainWindow::displayImage(QTreeWidgetItem *item){
  auto filename = item->data(colItem, Qt::UserRole).toString();
  labFile->setText(filename);
  // 保存原始副本
  pixmap.load(filename);
  on_actZoomFitH_triggered();
}

void MainWindow::on_actZoomFitH_triggered() {
  auto height_area = ui->scrollArea->height();
  auto height_image = pixmap.height();
  pixRatio = height_image * 1.0 / height_area;
  auto new_pixmap = pixmap.scaledToHeight(height_area - 30);
  ui->labPicture->setPixmap(new_pixmap);
}
```

# 13. 线程
## 13.1 基于信号槽通信
### 定义工作线程类
```c++
class DiceThread : public QThread {
  Q_OBJECT
  // ...
 signals:
  void NewValue(int seq, int dice_value);
 protected:
  void run() override;  // 重载线程 run 函数
 private:
  bool stop_;           // 线程主循环状态
};
```

### 实现 run 函数
```c++
void DiceThread::run() {
  // qsrand 是线程安全的
  qsrand(QTime::currentTime().msec());
  // 线程主循环
  while (!stop_) {
    if (!pause_) {
      dice_value_ = qrand() % 6 + 1;
      ++seq_;
      emit NewValue(seq_, dice_value_);
    }
    msleep(1000);
  }
  quit();
}
```

### 信号槽与主线程通信
```c++
// thread 定义在窗口控件中通过信号槽与 GUI 通信

// 关联相关信号
connect(&thread_, &DiceThread::started, this, &DiceDialog::onThreadStarted);
connect(&thread_, &DiceThread::finished, this, &DiceDialog::onThreadFinished);
connect(&thread_, &DiceThread::NewValue, this, &DiceDialog::onThreadNewValue);

// 启动线程
thread_.start();

// 阻塞线程, 一般需要在退出一类事件中对关联线程进行处理
void DiceDialog::closeEvent(QCloseEvent *event) {
  // 判断线程状态
  if (thread_.isRunning()) {
    // 修改线程状态位
    thread_.StopThread();
    // 阻塞线程
    thread_.wait();
  }
  event->accept();
}
```

## 13.2 基于互斥量通信

# 5. Model/View 结构

# 20. 串口开发
- 串口通信定义
- QSerialPortInfo, QSerialPort

## 设置串口
- 波特率 setBaudRate() 默认9600
- 数据位 setDataBits()
- 停止位 setStopBits() 停止位越多, 时钟异步的容忍越大, 传输速率越慢
- 奇偶校验位