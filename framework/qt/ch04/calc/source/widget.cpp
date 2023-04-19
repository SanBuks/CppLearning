#include "widget.h"
#include "ui_widget.h"

#include <QString>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() {
  delete ui;
}

void Widget::on_btnCalc_clicked() {
  auto num = ui->lEditNum->text().toInt();
  auto price = ui->lEditPrice->text().toFloat();
  auto total = num * price;
//ui->lEditPriceSum->setText(QString::asprintf("%.2f", total));
  ui->lEditPriceSum->setText(QString::number(total, 'f', 2));
}

void Widget::on_btnDec_clicked() {
  auto num = ui->lEditDec->text().toInt();

  QString str = QString::number(num, 2);
  ui->lEditBin->setText(str);
//str = str.setNum(num, 16).toUpper();
  str = QString::number(num, 16).toUpper();
  ui->lEditHex->setText(str);
}

void Widget::on_btnBin_clicked() {
  bool ok;
  auto num = ui->lEditBin->text().toInt(&ok, 2);

  QString str = QString::number(num, 10);
  ui->lEditDec->setText(str);
  str = QString::number(num, 16).toUpper();
  ui->lEditHex->setText(str);
}

void Widget::on_btnHex_clicked() {
  bool ok;
  auto num = ui->lEditHex->text().toInt(&ok, 16);

  QString str = QString::number(num, 10);
  ui->lEditDec->setText(str);
  str = QString::number(num, 2);
  ui->lEditBin->setText(str);
}