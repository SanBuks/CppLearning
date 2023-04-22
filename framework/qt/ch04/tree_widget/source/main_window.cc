#include "main_window.h"
#include "ui_main_window.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  initTree();

  labFile = new QLabel("");
  ui->statusbar->addWidget(labFile);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::initTree() {
  ui->treeWidget->clear();
  QIcon icon(":/images/image/15.ico");
  auto top_item = new QTreeWidgetItem(itTopItem);


  top_item->setIcon(colItem, icon);
  top_item->setText(colItem, "图片文件");
  top_item->setText(colItemType, "Type=itTopItem");

  top_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |
      Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);

  top_item->setCheckState(colItem, Qt::Checked);
  top_item->setData(colItem, Qt::UserRole, QVariant(QString("")));
  ui->treeWidget->addTopLevelItem(top_item);
}

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

void MainWindow::on_actAddFolder_triggered() {
  // 在 this 中央显示 FileDialog, 标题为"文件浏览", 工作目录为 "/d/"
  auto dir = QFileDialog::getExistingDirectory(this, "文件浏览", "/d/");
  if (!dir.isEmpty()) {
    auto parItem = ui->treeWidget->currentItem();
    if (!parItem) return;
    addFolderItem(parItem, dir);
  }
}

void MainWindow::addFolderItem(QTreeWidgetItem *parItem, const QString &dir) {
  QIcon icon(":/images/image/open3.bmp");
  auto folder_name = getFinalFolderName(dir);
  auto item = new QTreeWidgetItem(itGroupItem);

  // 根据 colNum 设置 text 或 icon
  item->setIcon(colItem, icon);
  item->setText(colItem, folder_name);
  item->setText(colItemType, "Type=itGroupItem");

  // 设置标志
  item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |
                 Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);

  item->setCheckState(colItem, Qt::Checked);
  // 设置数据
  item->setData(colItem, Qt::UserRole, QVariant(dir));
  parItem->addChild(item);
}

QString MainWindow::getFinalFolderName(const QString &fullPathName) {

  auto len = fullPathName.count();
  auto index = fullPathName.lastIndexOf("/");
  return fullPathName.right(len - index - 1);
}

void MainWindow::on_actAddFiles_triggered() {

  // 在 this 中央显示 FileDialog, 标题为"文件浏览", 工作目录为 "/d/"
  // 过滤只保留 Images 类文件
  auto files = QFileDialog::getOpenFileNames(this, "打开多个文件", "/d/",
                                             "Images(*.png *.xpm *.jpg)");
  if (!files.isEmpty()) {
    auto parItem = ui->treeWidget->currentItem();
    if (!parItem) return;
    addFileItems(parItem, files);
  }
}

void MainWindow::addFileItems(QTreeWidgetItem *parItem, const QStringList &files_path) {
  for (const auto &file_path : files_path) {
    QIcon icon(":/images/image/31.ico");
    auto file_name = getFinalFolderName(file_path);
    auto item = new QTreeWidgetItem(itImageItem);
    item->setIcon(colItem, icon);
    item->setText(colItem, file_name);
    item->setText(colItemType, "Type=itImageItem");
    item->setCheckState(colItem, Qt::Checked);
    item->setData(colItem,Qt::UserRole, QVariant(file_path));
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |
                   Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    parItem->addChild(item);
  }
}

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

void MainWindow::on_actDeleteItem_triggered() {
  auto item = ui->treeWidget->currentItem();
  if (!item) return;
  auto parItem = item->parent();
  parItem->removeChild(item);
  delete item;
  ui->treeWidget->setCurrentItem(parItem);
}

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current,
                                                  QTreeWidgetItem *previous) {
  Q_UNUSED(current);
  if (!current) return;
  auto type_ = current->type();
  switch (type_) {
    case itTopItem:
      ui->actAddFolder->setEnabled(true);
      ui->actAddFiles->setEnabled(true);
      ui->actDeleteItem->setEnabled(false);
      ui->actZoomFitH->setEnabled(false);
      ui->actZoomFitW->setEnabled(false);
      ui->actZoomIn->setEnabled(false);
      ui->actZoomOut->setEnabled(false);
      ui->actZoomRealSize->setEnabled(false);
      break;
    case itGroupItem:
      ui->actAddFolder->setEnabled(true);
      ui->actAddFiles->setEnabled(true);
      ui->actDeleteItem->setEnabled(true);
      ui->actZoomFitH->setEnabled(false);
      ui->actZoomFitW->setEnabled(false);
      ui->actZoomIn->setEnabled(false);
      ui->actZoomOut->setEnabled(false);
      ui->actZoomRealSize->setEnabled(false);
      break;
    case itImageItem:
      ui->actAddFolder->setEnabled(false);
      ui->actAddFiles->setEnabled(false);
      ui->actDeleteItem->setEnabled(true);
      ui->actZoomFitH->setEnabled(true);
      ui->actZoomFitW->setEnabled(true);
      ui->actZoomIn->setEnabled(true);
      ui->actZoomOut->setEnabled(true);
      ui->actZoomRealSize->setEnabled(true);
      displayImage(current);
      break;
    default:
      ;
  }
}

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

void MainWindow::on_actZoomFitW_triggered() {
  auto width_area = ui->scrollArea->width();
  auto width_image = pixmap.width();
  pixRatio = width_image * 1.0 / width_area;
  auto new_pixmap = pixmap.scaledToWidth(width_area - 30);
  ui->labPicture->setPixmap(new_pixmap);
}

void MainWindow::on_actZoomIn_triggered() {
  pixRatio *= 1.2;
  int width = static_cast<int>(pixRatio * pixmap.width());
  int height = static_cast<int>(pixRatio * pixmap.height());
  auto new_pixmap = pixmap.scaled(width, height);
  ui->labPicture->setPixmap(new_pixmap);
}

void MainWindow::on_actZoomOut_triggered() {
  pixRatio *= 0.8;
  int width = static_cast<int>(pixRatio * pixmap.width());
  int height = static_cast<int>(pixRatio * pixmap.height());
  auto new_pixmap = pixmap.scaled(width, height);
  ui->labPicture->setPixmap(new_pixmap);
}

void MainWindow::on_actZoomRealSize_triggered() {
  pixRatio = 1;
  ui->labPicture->setPixmap(pixmap);
}