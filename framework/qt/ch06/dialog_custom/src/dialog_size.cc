//
// Created by San on 2023/5/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_dialog_size.h" resolved

#include "include/dialog_size.h"
#include "ui_dialog_size.h"

DialogSize::DialogSize(QWidget *parent) :
    QDialog(parent), ui(new Ui::DialogSize) {
  ui->setupUi(this);
}

DialogSize::~DialogSize() {
  delete ui;
}
