#include "include/main_window.h"
#include "ui_main_window.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  labCellIndex = new QLabel("当前单元格坐标", this);
  labCellType = new QLabel("当前单元格类型", this);
  labStudID = new QLabel("学生 ID", this);

  labCellIndex->setMinimumWidth(100);
  labCellType->setMinimumWidth(100);
  labStudID->setMinimumWidth(100);

  ui->statusbar->addWidget(labCellIndex);
  ui->statusbar->addWidget(labCellType);
  ui->statusbar->addWidget(labStudID);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_btnSetHeader_clicked() {
  QStringList header;
  header << "姓名" << "性别" << "出生日期" << "民族" << "分数" << "是否是党员";
  ui->tableWidget->setColumnCount(header.count());
}
