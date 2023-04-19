#include "widget.h"
#include "ui_Widget.h"

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  this->setWindowTitle("串口调试");

  init();
}

Widget::~Widget() {
  delete ui;
}

void Widget::init() {
  // 获取串口
  auto ports = QSerialPortInfo::availablePorts();
  // 添加串口相关信息
  for (const auto &item : ports) {
    ui->cBoxPortSelect->addItem(
        item.portName() + ":" + item.description(), item.portName());
  }

  // 添加串口相关波特率
  auto baud_rates = QSerialPortInfo::standardBaudRates();
  for (const auto &item : baud_rates) {
    ui->cBoxBaudRate->addItem(QString::number(item), item);
  }

  // 设置停止位
  ui->cBoxStopBit->addItem("1", QSerialPort::OneStop);
  ui->cBoxStopBit->addItem("1.5", QSerialPort::OneAndHalfStop);
  ui->cBoxStopBit->addItem("2", QSerialPort::TwoStop);

  // 设置数据位
  ui->cBoxDataBit->addItem("5", QSerialPort::Data5);
  ui->cBoxDataBit->addItem("6", QSerialPort::Data6);
  ui->cBoxDataBit->addItem("7", QSerialPort::Data7);
  ui->cBoxDataBit->addItem("8", QSerialPort::Data8);

  // 设置校验位
  ui->cBoxParityBit->addItem("NoParity", QSerialPort::NoParity);
  ui->cBoxParityBit->addItem("EvenParity", QSerialPort::EvenParity);
  ui->cBoxParityBit->addItem("OddParity", QSerialPort::OddParity);
  ui->cBoxParityBit->addItem("SpaceParity", QSerialPort::SpaceParity);
  ui->cBoxParityBit->addItem("MarkParity", QSerialPort::MarkParity);

  connect(&port_, &QSerialPort::readyRead, this, &Widget::on_readyRead);
}

void Widget::on_btnOpenPort_released() {

  if (port_.isOpen()) {
    port_.close();
    ui->btnOpenPort->setText("打开串口");
    return;
  }

  auto port_name = ui->cBoxPortSelect->currentData().toString();
  auto baud_rate = ui->cBoxBaudRate->currentData().value<QSerialPort::BaudRate>();
  auto data_bits = ui->cBoxDataBit->currentData().value<QSerialPort::DataBits>();
  auto stop_bits = ui->cBoxStopBit->currentData().value<QSerialPort::StopBits>();
  auto parity_bits = ui->cBoxParityBit->currentData().value<QSerialPort::Parity>();

  port_.setPortName(port_name);
  port_.setBaudRate(baud_rate);
  port_.setDataBits(data_bits);
  port_.setStopBits(stop_bits);
  port_.setParity(parity_bits);

  if (!port_.open(QIODevice::ReadWrite)) {
    QMessageBox::warning(this, "warning",
                         port_name + " open failed: " + port_.errorString());
    return;
  } else {
    ui->btnOpenPort->setText("关闭串口");
  }
}

void Widget::on_readyRead() {
  auto data = port_.readAll();
  ui->ptxtEditRecv->setPlainText(QString::fromLocal8Bit(data));
}

void Widget::on_btnSend_released() {
  auto data = ui->ptxtEditSend->toPlainText();
  port_.write(data.toLocal8Bit());
}
