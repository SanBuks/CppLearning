#include "include/main_window.h"
#include "ui_main_window.h"

#include <QLabel>
#include <QDate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  labCellIndex = new QLabel("当前单元格坐标", this);
  labCellType = new QLabel("当前单元格类型", this);
  labStudID = new QLabel("学生 ID", this);

  labCellIndex->setMinimumWidth(100);
  labCellType->setMinimumWidth(100);
  labStudID->setMinimumWidth(100);

  ui->statusbar->addWidget(labCellIndex);
  ui->statusbar->addWidget(labCellType);
  ui->statusbar->addWidget(labStudID);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_btnSetHeader_clicked() {
  // 设计表头文字
  QStringList header;
  header << "姓名" << "性别" << "出生日期" << "民族" << "分数" << "是否是党员" ;
  ui->tableWidget->setColumnCount(header.count());

  // 简单设计表头
//  ui->tableWidget->setHorizontalHeaderLabels(header);

  // 自定义设计表头
  QTableWidgetItem *item;
  for (int i = 0; i < header.count(); ++i) {
    item = new QTableWidgetItem(header.at(i));
    QFont font = item->font();
    font.setBold(true);
    font.setPointSize(12);
    item->setTextColor(Qt::red);
    item->setFont(font);
    ui->tableWidget->setHorizontalHeaderItem(i, item);
  }
}

void MainWindow::on_btnIniData_clicked() {
  QString str_name, str_sex, str_ethnicity = "汉族";
  QDate date(1980, 4, 7); bool is_pm = false;
  auto row_count = ui->tableWidget->rowCount();
  for (int i = 0; i < row_count; ++i) {
    str_name = QString::asprintf("学生 %d", i);
    str_sex = i % 2 ? "男" : "女";
    date.addDays(20);
    is_pm = !is_pm;
    CreateARow(i, str_name, str_sex, date, str_ethnicity, is_pm, 70);
  }
}

void MainWindow::on_btnSetRows_clicked() {
  auto row_count = ui->spinRowCount->value();
  ui->tableWidget->setRowCount(row_count);
  bool is_color = ui->chkBoxRowColor->isChecked();
  ui->tableWidget->setAlternatingRowColors(is_color);
}

void MainWindow::CreateARow(int row, const QString &name, const QString &sex, QDate date,
                  const QString &ethnicity, bool is_pm, int score) {
  QTableWidgetItem *item;
  // name
  item = new QTableWidgetItem(name, CTName);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  item->setData(Qt::UserRole, QVariant(kStuId + row));
  ui->tableWidget->setItem(row, COLName, item);
  // sex
  item = new QTableWidgetItem(sex, CTSex);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  QIcon icon;
  if (sex == "男") {
    icon.addFile("/images/icons/boy.ico");
  } else {
    icon.addFile("/images/icons/girl.ico");
  }
  item->setIcon(icon);
  ui->tableWidget->setItem(row, COLSex, item);
  //date
  item = new QTableWidgetItem(date.toString("yyyy-MM-dd"), CTBirth);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  ui->tableWidget->setItem(row, COLBirth, item);
  //ethnicity
  item = new QTableWidgetItem(ethnicity, CTEthnicity);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  ui->tableWidget->setItem(row, COLEthnicity, item);
  //score
  item = new QTableWidgetItem(QString::asprintf("%d", score), CTScore);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  ui->tableWidget->setItem(row, COLScore, item);
  //pm
  item = new QTableWidgetItem("党员", CTPM);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  if (is_pm) {
    item->setCheckState(Qt::Checked);
  } else {
    item->setCheckState(Qt::Unchecked);
  }
  item->setBackground(Qt::yellow);
  ui->tableWidget->setItem(row, COLPM, item);
}

void MainWindow::on_btnInsertRow_clicked() {
  auto cur_row = ui->tableWidget->currentRow();
  ui->tableWidget->insertRow(cur_row);
  CreateARow(cur_row, "新学生", "男", QDate::fromString("1999-01-01", "yyyy-MM-dd"),
             "汉族", true, 88);
}

void MainWindow::on_btnAppendRow_clicked() {
  auto row_count = ui->tableWidget->rowCount();
  ui->tableWidget->insertRow(row_count);
  CreateARow(row_count, "新学生2", "男", QDate::fromString("1999-01-01", "yyyy-MM-dd"),
             "汉族", true, 88);
}

void MainWindow::on_btnDelCurRow_clicked() {
  auto cur_row = ui->tableWidget->currentRow();
  ui->tableWidget->removeRow(cur_row);
}

void MainWindow::on_btnAutoHeght_clicked() {
  ui->tableWidget->resizeRowsToContents();
}

void MainWindow::on_btnAutoWidth_clicked() {
  ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_btnReadToEdit_clicked() {
  QString str;
  for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
    str = QString::asprintf("第 %d 行:", i + 1);
    for (int j = 0; j < ui->tableWidget->columnCount() - 1; ++j) {
      str += " " + ui->tableWidget->item(i, j)->text();
    }
    if (ui->tableWidget->item(i, FieldColNum::COLPM)->checkState()) {
      str += " pm";
    } else {
      str += " no_pm";
    }

    ui->plainTextEdit->appendPlainText(str);
  }
}

void MainWindow::on_chkBoxRowColor_clicked(bool checked) {
  ui->tableWidget->setAlternatingRowColors(checked);
}

void MainWindow::on_chkBoxTabEditable_clicked(bool checked) {
  if (checked) {
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked |
                                     QAbstractItemView::SelectedClicked);
  } else {
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  }
}

void MainWindow::on_chkBoxHeaderH_clicked(bool checked) {
  ui->tableWidget->horizontalHeader()->setVisible(checked);
}

void MainWindow::on_chkBoxHeaderV_clicked(bool checked) {
  ui->tableWidget->verticalHeader()->setVisible(checked);
}

void MainWindow::on_rBtnSelectItem_clicked() {
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void MainWindow::on_rBtnSelectRow_clicked() {
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::on_tableWidget_currentCellChanged(int currentRow, int currentColumn,
                                                   int previousRow, int previousColumn) {
  Q_UNUSED(previousRow)
  Q_UNUSED(previousColumn)

  auto item = ui->tableWidget->item(currentRow, currentColumn);
  if (!item) return;

  labCellIndex->setText(QString::asprintf("第 %d 行, %d 列", currentRow, currentColumn));
  labCellType->setText(QString::asprintf("类型 %d", item->type()));
  if (item->data(Qt::UserRole).isValid()) {
    labStudID->setText(QString::asprintf("数据 %d", item->data(Qt::UserRole).toInt()));
  } else {
    labStudID->setText(QString::asprintf("数据 %d", 0));
  }
}
