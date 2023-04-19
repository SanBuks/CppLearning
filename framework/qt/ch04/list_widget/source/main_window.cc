#include "main_window.h"
#include "ui_main_window.h"

#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setCentralWidget(ui->splitter);
  this->setWindowTitle("ListWidget 与 ToolButton 测试");

  // 将 ToolButton 与 Action 绑定
  ui->tbtnListIni->setDefaultAction(ui->actListIni);
  ui->tbtnListClear->setDefaultAction(ui->actListClear);
  ui->tbtnListInsert->setDefaultAction(ui->actListInsert);
  ui->tbtnListAppend->setDefaultAction(ui->actListAppend);
  ui->tbtnListDelete->setDefaultAction(ui->actListDelete);

  ui->tBtnSelALL->setDefaultAction(ui->actSelALL);
  ui->tBtnSelNone->setDefaultAction(ui->actSelNone);
  ui->tBtnSelInvs->setDefaultAction(ui->actSelInvs);

  // 创建 menu, 给 menu 增加 Action
  QMenu *menu = new QMenu(this);
  menu->addAction(ui->actSelALL);
  menu->addAction(ui->actSelNone);
  menu->addAction(ui->actSelInvs);
  // 给 Action 增加 menu
  ui->actSelPopMenu->setMenu(menu);

  // 增加到工具栏 和 Tool Button 上
  ui->toolBar->addAction(ui->actSelPopMenu);
  ui->toolBar->addAction(ui->actQuit);
  ui->tBtnSelectItem->setDefaultAction(ui->actSelPopMenu);

  // 增加右键菜单
  ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_toolBox_currentChanged(int index) {
  ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::on_actListIni_triggered() {
  ui->listWidget->clear();
  QIcon icon(":/images/image/check2.ico");
  bool chk = ui->chkBoxListEditable->isChecked();

  for (int i = 0; i < 20; ++i) {
    QString txt = QString::asprintf("item %d", i);
    auto *item = new QListWidgetItem(txt);
    item->setIcon(icon);
    item->setCheckState(Qt::Checked);
    if (chk) {
      item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable |
                     Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    } else {
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |
                     Qt::ItemIsEnabled);
    }
    ui->listWidget->addItem(item);
  }
}

void MainWindow::on_actListClear_triggered() {
  ui->listWidget->clear();
}

void MainWindow::on_actListInsert_triggered() {
  QIcon icon(":/images/image/check2.ico");
  bool chk = ui->chkBoxListEditable->isChecked();
  auto *item = new QListWidgetItem("Inserted Item");
  item->setIcon(icon);
  item->setCheckState(Qt::Checked);
  auto mask = chk ? Qt::ItemIsEditable : Qt::NoItemFlags;
  item->setFlags(mask| Qt::ItemIsSelectable |
                 Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
  ui->listWidget->insertItem(ui->listWidget->currentRow(), item);
}

void MainWindow::on_actListAppend_triggered() {
  QIcon icon(":/images/image/check2.ico");
  bool chk = ui->chkBoxListEditable->isChecked();
  auto *item = new QListWidgetItem("Appended Item");
  item->setIcon(icon);
  item->setCheckState(Qt::Checked);
  auto mask = chk ? Qt::ItemIsEditable : Qt::NoItemFlags;
  item->setFlags(mask | Qt::ItemIsSelectable |
                 Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
  ui->listWidget->addItem(item);
}

void MainWindow::on_actListDelete_triggered() {
  int row = ui->listWidget->currentRow();
  auto item = ui->listWidget->takeItem(row);
  delete item;
}

void MainWindow::on_actSelALL_triggered() {
  int cnt = ui->listWidget->count();
  for (int i = 0; i < cnt; ++i) {
    auto item = ui->listWidget->item(i);
    item->setCheckState(Qt::Checked);
  }
}

void MainWindow::on_actSelNone_triggered() {
  int cnt = ui->listWidget->count();
  for (int i = 0; i < cnt; ++i) {
    auto item = ui->listWidget->item(i);
    item->setCheckState(Qt::Unchecked);
  }
}

void MainWindow::on_actSelInvs_triggered() {
  int cnt = ui->listWidget->count();
  for (int i = 0; i < cnt; ++i) {
    auto item = ui->listWidget->item(i);
    if (item->checkState()) {
      item->setCheckState(Qt::Unchecked);
    } else {
      item->setCheckState(Qt::Checked);
    }
  }
}

void MainWindow::on_chkBoxListEditable_clicked(bool checked) {
  int cnt = ui->listWidget->count();
  auto mask = checked ? Qt::ItemIsEditable : Qt::NoItemFlags;
  for (int i = 0; i < cnt; ++i) {
    auto item = ui->listWidget->item(i);
    item->setFlags(mask | Qt::ItemIsSelectable |
                   Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
  }
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current,
                                                  QListWidgetItem *previous) {
  if (current && previous) {
    ui->editCutItemText->setText("上一项:" + previous->text() +
                                 " 当前项: " + current->text());
  } else if (current) {
    ui->editCutItemText->setText("当前项: " + current->text());
  } else {
    ui->editCutItemText->setText("无数据项");
  }
}

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