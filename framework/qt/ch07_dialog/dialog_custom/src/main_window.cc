#include "include/main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actTab_SetSize_triggered() {
//  ui->tableView->
}

