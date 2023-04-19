#include "widget.h"
#include "ui_Widget.h"

#include <QTextBlock>
#include <QMenu>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() {
  delete ui;
}

void Widget::on_btnIniItems_clicked() {
  QIcon icon(":/images/image/aim.ico");
  ui->comboBox->clear();
  for (int i = 0; i < 20; ++i) {
    ui->comboBox->addItem(icon, QString::asprintf("Item %d", i));
  }
}
void Widget::on_btnClearItems_clicked() {
  ui->comboBox->clear();

}
void Widget::on_btnIni2_clicked() {
  ui->comboBox2->clear();
  QIcon icon(":/images/image/aim.ico");
  QMap<QString, int> city_zone;
  city_zone.insert("南京", 10);
  city_zone.insert("无锡", 20);
  city_zone.insert("苏州", 30);
  auto keys_tmp = city_zone.keys();
  for(const auto &item : keys_tmp) {
    ui->comboBox2->addItem(icon, item, city_zone[item]);
  }
}
void Widget::on_comboBox_currentIndexChanged(const QString &str) {
  if (!str.isEmpty()) {
    ui->plainTextEdit->appendPlainText(str);
  }
}
void Widget::on_comboBox2_currentIndexChanged(const QString &str) {
  if (!str.isEmpty()) {
    auto zone = ui->comboBox2->currentData();
    ui->plainTextEdit->appendPlainText(str + ": " + zone.toString());
  }
}
void Widget::on_chkBoxEditable_clicked(bool clicked) {
  ui->comboBox->setEnabled(clicked);
}
void Widget::on_btnClearText_clicked() {
  ui->plainTextEdit->clear();
}
void Widget::on_chkBoxReadonly_clicked(bool clicked) {
  ui->plainTextEdit->setReadOnly(clicked);
}
void Widget::on_btnToComboBox_clicked() {
  auto doc = ui->plainTextEdit->document();
  QIcon icon(":/images/image/aim.ico");
  auto num = doc->blockCount();
  for (int i = 0; i < num; ++i) {
    auto text = doc->findBlockByNumber(i).text();
    ui->comboBox->addItem(icon, text);
  }
}
void Widget::on_plainTextEdit_customContextMenuRequested(const QPoint &point) {
  QMenu *p = ui->plainTextEdit->createStandardContextMenu();
  p->exec(point);
}
