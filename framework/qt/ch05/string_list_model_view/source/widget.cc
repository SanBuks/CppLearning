//
// Created by San on 2023/4/14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Widget.h" resolved

#include "widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget),
    string_list_model(new QStringListModel(this)) {
  ui->setupUi(this);
  QStringList list;
  list << "item1" << "item2" << "item3" << "item4" << "item5";
  string_list_model->setStringList(list);
  ui->listView->setModel(string_list_model);
  ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked |
                                QAbstractItemView::SelectedClicked);
}

Widget::~Widget() {
  delete ui;
}
void Widget::on_btnTextClear_clicked() {
  ui->plainTextEdit->clear();
}
void Widget::on_btnTextImport_clicked() {
  ui->plainTextEdit->clear();
  QStringList list = string_list_model->stringList();
  for (const auto &str : list) {
    ui->plainTextEdit->appendPlainText(str);
  }
}
void Widget::on_btnIniList_clicked() {
  QStringList list;
  list << "item1" << "item2" << "item3" << "item4" << "item5";
  string_list_model->setStringList(list);
}
void Widget::on_btnListClear_clicked() {
  string_list_model->removeRows(0, string_list_model->rowCount());
}
void Widget::on_btnListDelete_clicked() {
  string_list_model->removeRow(ui->listView->currentIndex().row());
}
void Widget::on_btnListAppend_clicked() {
  string_list_model->insertRow(string_list_model->rowCount());
  QModelIndex index = string_list_model->index(string_list_model->rowCount() - 1, 0);
  string_list_model->setData(index, "appended Item", Qt::DisplayRole);
  ui->listView->setCurrentIndex(index);
}
void Widget::on_btnListInsert_clicked() {
  auto current_row = ui->listView->currentIndex().row();
  string_list_model->insertRow(current_row);
  QModelIndex index = string_list_model->index(current_row, 0);
  string_list_model->setData(index, "inserted Item", Qt::DisplayRole);
  ui->listView->setCurrentIndex(index);
}
void Widget::on_listView_clicked(const QModelIndex &index) {
  ui->LabInfo->setText(
      QString::asprintf("%d 行 %d 列", index.row(), index.column()));
}
