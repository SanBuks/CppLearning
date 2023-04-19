//
// Created by San on 2023/4/14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_window.h" resolved

#include "main_window.h"
#include "ui_main_window.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
    file_model(new QFileSystemModel(this)){
  ui->setupUi(this);
  file_model->setRootPath(QDir::currentPath());
  ui->treeView->setModel(file_model);
  ui->listView->setModel(file_model);
  ui->tableView->setModel(file_model);
  ui->tableView->verticalHeader()->setVisible(false);
  connect(ui->treeView, SIGNAL(clicked(QModelIndex)),
          ui->listView, SLOT(setRootIndex(QModelIndex)));
  connect(ui->treeView, SIGNAL(clicked(QModelIndex)),
          ui->tableView, SLOT(setRootIndex(QModelIndex)));
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index) {
  ui->labName->setText(file_model->fileName(index));
  ui->labType->setText(file_model->type(index));
  ui->labPath->setText(file_model->filePath(index));
  ui->checkBox->setChecked(file_model->isDir(index));

  auto size = file_model->size(index) / 1024;
  if (size < 1024) {
    ui->labSize->setText(QString::asprintf("%d KB", size));
  } else {
    ui->labSize->setText(QString::asprintf("%.2f MB", (double) size / 1024));
  }
}
