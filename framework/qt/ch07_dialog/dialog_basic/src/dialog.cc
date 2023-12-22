#include "include/dialog.h"
#include "ui_Dialog.h"

#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>

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
  QPalette::ColorRole color_role = QPalette::Text; //  QPalette::Base

  auto palette = ui->plainTextEdit->palette();
  auto init_color = palette.color(color_role);
  auto color = QColorDialog::getColor(init_color, this, "选择颜色");
  if (color.isValid()) {
    palette.setColor(color_role, color);
    ui->plainTextEdit->setPalette(palette);
  }
}

void Dialog::on_btnFont_clicked() {
  bool ok = false;
  auto init_font = ui->plainTextEdit->font();
  auto font = QFontDialog::getFont(&ok, init_font);
  if (ok) {
    ui->plainTextEdit->setFont(font);
  }
}

void Dialog::on_btnInputString_clicked() {
  QString title = "输入对话框";
  QString lab = "请输入文字";
  QString default_str = "初始文字";
  bool ok; // QLineEdit::EchoMode::Normal, NoEcho, Password, PasswordEchoOnEdit
  QString text = QInputDialog::getText(this, title, lab,
                                       QLineEdit::Normal, default_str, &ok,
                                       Qt::WindowType::MSWindowsFixedSizeDialogHint);
// Qt::WindowType::MSWindowsFixedSizeDialogHint);
// 解决 setGeometry: Unable to set geometry 问题

  if (ok && !text.isEmpty()) {
    ui->plainTextEdit->appendPlainText(text);
  }
}

void Dialog::on_btnInputItem_clicked() {
  QStringList list{"a", "b", "c"};
  QString title = "输入对话框";
  QString lab = "请输入文字";
  bool ok = false;
  bool editable = true;
  int cur_index = 0;
  auto item = QInputDialog::getItem(this, title, lab, list, cur_index,
                                            editable, &ok, Qt::WindowType::MSWindowsFixedSizeDialogHint);
  if (ok && !item.isEmpty()) {
    ui->plainTextEdit->appendPlainText(item);
  }
}

void Dialog::on_btnInputInt_clicked() {
  QString title = "输入对话框";
  QString lab = "请输入字体大小数字";
  int default_size = ui->plainTextEdit->font().pointSize();
  int min = 1, max = 20, step = 1;
  bool ok = false;
  auto size = QInputDialog::getInt(this, title, lab, default_size,
                                   min, max, step, &ok,
                                   Qt::WindowType::MSWindowsFixedSizeDialogHint);
  if (ok) {
    auto font = ui->plainTextEdit->font();
    font.setPointSize(size);
    ui->plainTextEdit->setFont(font);
  }
}

void Dialog::on_btnInputFloat_clicked() {
  QString title = "输入对话框";
  QString lab = "请输入字体大小数字";
  double default_size = ui->plainTextEdit->font().pointSizeF();
  double min = 1.0, max = 20.0; int decimals = 2;
  bool ok = false;
  auto size = QInputDialog::getDouble(this, title, lab, default_size,
                                              min, max, decimals, &ok,
                                              Qt::WindowType::MSWindowsFixedSizeDialogHint);
  if (ok) {
    auto font = ui->plainTextEdit->font();
    font.setPointSizeF(size);
    ui->plainTextEdit->setFont(font);
  }
}

void Dialog::on_btnMsgInformation_clicked() {
  QString title = "通知消息框";
  QString info = "通知消息";
  QMessageBox::information(this, title, info,
                           QMessageBox::StandardButton::Ok,
                           QMessageBox::StandardButton::Yes,
                           QMessageBox::StandardButton::No);
//  QMessageBox::warning;
//  QMessageBox::critical;
//  QMessageBox::about;

}

void Dialog::on_btnMsgQuestion_clicked() {
  QString title = "选择消息框";
  QString info = "选择消息";
  auto result = QMessageBox::question(this, title, info,
                                      QMessageBox::StandardButton::Yes |
                                      QMessageBox::StandardButton::No |
                                      QMessageBox::StandardButton::Cancel,
                                      QMessageBox::StandardButton::NoButton);
  if (result == QMessageBox::StandardButton::Yes) {
    ui->plainTextEdit->appendPlainText("Yes");
  } else if (result == QMessageBox::StandardButton::No) {
    ui->plainTextEdit->appendPlainText("No");
  } else if (result == QMessageBox::StandardButton::Cancel) {
    ui->plainTextEdit->appendPlainText("Cancel");
  } else {
    ui->plainTextEdit->appendPlainText("No Button");
  }
}
