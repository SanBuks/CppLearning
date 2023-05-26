#include "include/dialog.h"
#include "ui_Dialog.h"

#include <QFileDialog>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
}

Dialog::~Dialog() {
  delete ui;
}

void Dialog::on_btnClearText_clicked() {
  ui->plainTextEdit->clear();
}

void Dialog::on_btnOpen_clicked() {
  QString dir = QDir::currentPath();
  QString title = "请选择文件";
  QString filter = "文本文件(*.txt);;所有图片(*.png *.jpg);;所有文件(*.*)";
  auto file_name = QFileDialog::getOpenFileName(this, title, dir, filter);
  if (file_name.isEmpty()) return;
  ui->plainTextEdit->appendPlainText(file_name);
}

void Dialog::on_btnOpenMulti_clicked() {
  QString dir = QDir::currentPath();
  QString title = "请选择文件";
  QString filter = "文本文件(*.txt);;所有图片(*.png *.jpg);;所有文件(*.*)";
  auto file_names = QFileDialog::getOpenFileNames(this, title, dir, filter);
  for (const auto &item : file_names) {
    if (item.isEmpty()) continue;
    ui->plainTextEdit->appendPlainText(item);
  }
}

void Dialog::on_btnSelDir_clicked() {
  QString dir = QDir::currentPath();
  QString title = "请选择目录";
  auto dir_name = QFileDialog::getExistingDirectory(this, title, dir, QFileDialog::ShowDirsOnly);
  if (dir_name.isEmpty()) return;
  ui->plainTextEdit->appendPlainText(dir_name);
}

void Dialog::on_btnSave_clicked() {
  QString dir = QDir::currentPath();
  QString title = "请选择目录";
  QString filter = "文本文件(*.txt);;所有图片(*.png *.jpg);;所有文件(*.*)";
  auto file_name = QFileDialog::getSaveFileName(this, title, dir, filter);
  if (file_name.isEmpty()) return;
  ui->plainTextEdit->appendPlainText(file_name);
}

void Dialog::on_btnColor_clicked() {

}

