#include "widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  connect(ui->SliderGreen, SIGNAL(valueChanged(int)),
          this, SLOT(on_SliderRed_valueChanged(int)));
  connect(ui->SliderBlue, SIGNAL(valueChanged(int)),
          this, SLOT(on_SliderRed_valueChanged(int)));
  connect(ui->SliderAlpha, SIGNAL(valueChanged(int)),
          this, SLOT(on_SliderRed_valueChanged(int)));
}

Widget::~Widget() {
  delete ui;
}

void Widget::on_SliderRed_valueChanged(int value) {
  Q_UNUSED(value);
  auto R = ui->SliderRed->value();
  auto G = ui->SliderGreen->value();
  auto B = ui->SliderBlue->value();
  auto alpha = ui->SliderAlpha->value();
  QColor color(R, G, B, alpha);
  auto pal = ui->textEdit->palette();
  pal.setColor(QPalette::Base, color);
  ui->textEdit->setPalette(pal);
}

void Widget::on_SliderH_valueChanged(int value) {
  ui->ScrollBarH->setValue(value);
  ui->progBarH->setValue(value);
}

void Widget::on_SliderV_valueChanged(int value) {
  ui->ScrollBarV->setValue(value);
  ui->progBarV->setValue(value);
}

void Widget::on_radioBtnDec_clicked() {
  ui->LCDDisplay->setDigitCount(3);
  ui->LCDDisplay->setDecMode();
}
void Widget::on_radioBtnBin_clicked() {
  ui->LCDDisplay->setDigitCount(8);
  ui->LCDDisplay->setBinMode();
}
void Widget::on_radioBtnHex_clicked() {
  ui->LCDDisplay->setDigitCount(3);
  ui->LCDDisplay->setHexMode();
}
void Widget::on_radioBtnOct_clicked() {
  ui->LCDDisplay->setDigitCount(4);
  ui->LCDDisplay->setOctMode();
}

void Widget::on_dial_valueChanged(int value) {
  ui->LCDDisplay->display(value);
}