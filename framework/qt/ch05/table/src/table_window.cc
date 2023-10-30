#include "table_window.h"
#include "ui_table_window.h"

#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

constexpr const int TableWindow::FixedRowCount;
constexpr const int TableWindow::FixedColumnCount;

TableWindow::TableWindow(QWidget *parent) :
    QMainWindow(parent),
    lab_file_(new QLabel("当前文件:", this)),
    lab_pos_(new QLabel("当前位置:", this)),
    lab_cell_text_(new QLabel("当前内容:", this)),
    item_model_(new QStandardItemModel(FixedRowCount, FixedColumnCount, this)),
    item_selection_model_(new QItemSelectionModel(item_model_, this)),
    ui(new Ui::TableWindow) {

  ui->setupUi(this);

  ui->tableView->setModel(item_model_);
  ui->tableView->setSelectionModel(item_selection_model_);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

  lab_file_->setMinimumWidth(200);
  lab_pos_->setMinimumWidth(150);
  lab_cell_text_->setMinimumWidth(300);
  ui->statusbar->addWidget(lab_file_);
  ui->statusbar->addWidget(lab_pos_);
  ui->statusbar->addWidget(lab_cell_text_);

  InitConnection();
}

TableWindow::~TableWindow() {
  delete ui;
}

void TableWindow::OnItemChanged(const QModelIndex &current, const QModelIndex &previous) {
  Q_UNUSED(previous)
  if (!current.isValid()) return;
  auto item = item_model_->itemFromIndex(current);
  lab_pos_->setText(QString::asprintf("当前位置: %d 行, %d 列", current.row() + 1, current.column() + 1));
  lab_cell_text_->setText(item->text());
  ui->actFontBold->setChecked(item->font().bold());
}

void TableWindow::OnOpenFile() {
  QString filename = QFileDialog::getOpenFileName(this, "打开文件", QCoreApplication::applicationDirPath(),
                                                  "数据文件(*.txt);所有文件(*.*)");
  if (filename.isEmpty()) return;

  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

  QStringList file_content;
  QTextStream stream(&file);
  ui->plainTextEdit->clear();
  while (!stream.atEnd()) {
    auto line = stream.readLine();
    ui->plainTextEdit->appendPlainText(line);
    file_content.append(line);
  }
  file.close();
  lab_file_->setText("当前文件: " + filename);

  ui->actAppend->setEnabled(true);
  ui->actDelete->setEnabled(true);
  ui->actInsert->setEnabled(true);
  ui->actSave->setEnabled(true);
  InitModelData(file_content);
}

void TableWindow::OnAppend() {
  QList<QStandardItem *> items;

  for (int i = 0; i < FixedColumnCount - 1; ++i) {
    items << new QStandardItem("0");
  }
  QString str = item_model_->headerData(FixedColumnCount - 1, Qt::Orientation::Horizontal).toString();
  auto item = new QStandardItem(str + ": ");
  item->setCheckable(true);
  items << item;
  item_model_->insertRow(item_model_->rowCount(), items);

  item_selection_model_->clearSelection();
  item_selection_model_->setCurrentIndex(item_model_->index(item_model_->rowCount() - 1, 0),
                                         QItemSelectionModel::Select);
}

void TableWindow::OnInsert() {
  auto index = item_selection_model_->currentIndex();
  if (!index.isValid()) return;

  QList<QStandardItem *> items;

  for (int i = 0; i < FixedColumnCount - 1; ++i) {
    items << new QStandardItem("0");
  }
  QString str = item_model_->headerData(FixedColumnCount - 1, Qt::Orientation::Horizontal).toString();
  auto item = new QStandardItem(str + ": ");
  item->setCheckable(true);
  items << item;
  item_model_->insertRow(index.row(), items);

  item_selection_model_->clearSelection();
  item_selection_model_->setCurrentIndex(index, QItemSelectionModel::Select);
}

void TableWindow::OnDelete() {
  auto index = item_selection_model_->currentIndex();
  if (!index.isValid()) return;

  item_model_->removeRow(index.row());
  int new_row = index.row() >= item_model_->rowCount() ? item_model_->rowCount() - 1 : index.row();
  item_selection_model_->setCurrentIndex(item_model_->index(new_row, 0), QItemSelectionModel::Select);
}

void TableWindow::OnBold(bool triggered) {
  if (!item_selection_model_->hasSelection()) return;

  auto indexes = item_selection_model_->selectedIndexes();
  for (auto index : indexes) {
    auto item = item_model_->itemFromIndex(index);
    QFont font;
    font.setBold(triggered);
    item->setFont(font);
  }
}

void TableWindow::OnLeft() {
  if (!item_selection_model_->hasSelection()) return;

  auto indexes = item_selection_model_->selectedIndexes();
  for (auto index : indexes) {
    auto item = item_model_->itemFromIndex(index);
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  }
}

void TableWindow::OnCenter() {
  if (!item_selection_model_->hasSelection()) return;

  auto indexes = item_selection_model_->selectedIndexes();
  for (auto index : indexes) {
    auto item = item_model_->itemFromIndex(index);
    item->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
  }
}

void TableWindow::OnRight() {
  if (!item_selection_model_->hasSelection()) return;

  auto indexes = item_selection_model_->selectedIndexes();
  for (auto index : indexes) {
    auto item = item_model_->itemFromIndex(index);
    item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
  }
}

void TableWindow::OnShow() {
  ui->plainTextEdit->clear();

  QString str;
  for (int i = 0; i < FixedColumnCount; ++i) {
    str += item_model_->horizontalHeaderItem(i)->text() + "\t";
  }
  ui->plainTextEdit->appendPlainText(str);

  for (int r = 0; r < item_model_->rowCount(); ++r) {
    str = "";
    for (int c = 0; c < FixedColumnCount - 1; ++c) {
      str += item_model_->item(r, c)->text() + "\t\t";
    }
    str += item_model_->item(r, FixedColumnCount - 1)->checkState() != Qt::CheckState::Unchecked ? "1" : "0";
    ui->plainTextEdit->appendPlainText(str);
  }
}

void TableWindow::OnSave() {
  QString filename = QFileDialog::getOpenFileName(this, "打开文件", QCoreApplication::applicationDirPath(),
                                                  "数据文件(*.txt);所有文件(*.*)");
  if (filename.isEmpty()) return;
  QFile file(filename);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
  QTextStream stream(&file);

  QString str;
  for (int i = 0; i < FixedColumnCount; ++i) {
    str += item_model_->horizontalHeaderItem(i)->text() + "\t";
  }
  stream << str << "\n";

  for (int r = 0; r < item_model_->rowCount(); ++r) {
    str = "";
    for (int c = 0; c < FixedColumnCount - 1; ++c) {
      str += item_model_->item(r, c)->text() + "\t";
    }
    str += item_model_->item(r, FixedColumnCount - 1)->checkState() != Qt::CheckState::Unchecked ? "1" : "0";
    stream << str << "\n";
  }
}

void TableWindow::InitConnection() {
  connect(item_selection_model_, &QItemSelectionModel::currentChanged, this, &TableWindow::OnItemChanged);

  connect(ui->actOpen, &QAction::triggered, this, &TableWindow::OnOpenFile);
  connect(ui->actAppend, &QAction::triggered, this, &TableWindow::OnAppend);
  connect(ui->actDelete, &QAction::triggered, this, &TableWindow::OnDelete);
  connect(ui->actInsert, &QAction::triggered, this, &TableWindow::OnInsert);
  connect(ui->actExit, &QAction::triggered, this, &TableWindow::close);

  connect(ui->actFontBold, &QAction::triggered, this, &TableWindow::OnBold);

  connect(ui->actAlignLeft, &QAction::triggered, this, &TableWindow::OnLeft);
  connect(ui->actAlignRight, &QAction::triggered, this, &TableWindow::OnRight);
  connect(ui->actAlignCenter, &QAction::triggered, this, &TableWindow::OnCenter);

  connect(ui->actModelData, &QAction::triggered, this, &TableWindow::OnShow);
  connect(ui->actSave, &QAction::triggered, this, &TableWindow::OnSave);
}

void TableWindow::InitModelData(QStringList file_content) {
  int row_count = file_content.size();
  item_model_->setRowCount(row_count - 1);
  QString header = file_content[0];
  QStringList header_list = header.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);
  item_model_->setHorizontalHeaderLabels(header_list);

  QStandardItem *item;
  for (int i = 1; i < row_count; ++i) {
    QString line = file_content[i];
    QStringList line_list = line.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);

    int j;
    for (j = 0; j < FixedColumnCount - 1; ++j) {
      item = new QStandardItem(line_list.at(j));
      item_model_->setItem(i - 1, j, item);
    }

    item = new QStandardItem(u8"测井取样: " + line_list[j]);
    item->setCheckable(true);
    item->setBackground(QBrush(Qt::yellow));
    item->setCheckState(!(line_list[j] == "0") ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    item_model_->setItem(i - 1, j, item);
  }
}
