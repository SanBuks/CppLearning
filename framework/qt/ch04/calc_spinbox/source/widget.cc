#include "widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() {
  delete ui;
}

void Widget::on_btnCalc_clicked() {
  auto num = ui->sBoxNum->value();
  auto price = ui->sBoxPrice->value();
  auto total = num * price;
  ui->sBoxPriceSum->setValue(total);
}

void Widget::on_btnDec_clicked() {
  auto num = ui->sBoxDec->value();
  ui->sBoxBin->setValue(num);
  ui->sBoxHex->setValue(num);
}

void Widget::on_btnBin_clicked() {
  auto num = ui->sBoxBin->value();
  ui->sBoxDec->setValue(num);
  ui->sBoxHex->setValue(num);
}

void Widget::on_btnHex_clicked() {
  auto num = ui->sBoxHex->value();
  ui->sBoxDec->setValue(num);
  ui->sBoxBin->setValue(num);
}
