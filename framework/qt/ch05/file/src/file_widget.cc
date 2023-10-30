//
// Created by San on 2023/10/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_file_widget.h" resolved

#include "header/file_widget.h"
#include "ui_file_widget.h"

FileWidget::FileWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::FileWidget) {

  ui->setupUi(this);

  file_system_model_ = new QFileSystemModel(this);
  file_system_model_->setRootPath(QDir::currentPath());

  ui->listView->setModel(file_system_model_);
  ui->treeView->setModel(file_system_model_);
  ui->tableView->setModel(file_system_model_);
  ui->tableView->verticalHeader()->setVisible(false);


  connect(ui->treeView, &QTreeView::clicked,
          ui->listView, &QListView::setRootIndex);
  connect(ui->treeView, &QTreeView::clicked,
          ui->tableView, &QTableView::setRootIndex);

  connect(ui->treeView, &QTreeView::clicked,
          this, &FileWidget::onTreeViewClicked);
}

FileWidget::~FileWidget() {
  delete ui;
}

void FileWidget::onTreeViewClicked(const QModelIndex &index) {

  qreal size = static_cast<qreal>(file_system_model_->size(index)) / 1024;
  QString sizeStr = size < 1024 ? QString::asprintf("%d.2 KB", size) :
                                  QString::asprintf("%f.2 MB", size / 1024);

  ui->labName->setText(file_system_model_->fileName(index));
  ui->labSize->setText(sizeStr);
  ui->cbxDir->setChecked(file_system_model_->isDir(index));
  ui->labPath->setText(file_system_model_->filePath(index));

}
