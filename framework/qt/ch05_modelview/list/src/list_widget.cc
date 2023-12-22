#include "list_widget.h"
#include "ui_list_widget.h"

#include <QDebug>

ListWidget::ListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListWidget),
    list_model_(new QStringListModel) {
  ui->setupUi(this);
  ui->listView->setModel(list_model_);
  InitList();
  InitConnection();
}

ListWidget::~ListWidget() {
  delete ui;
  delete list_model_;
}

void ListWidget::OnBtnShowPlainClicked() {
  for (auto &item : list_model_->stringList()) {
    ui->plainTextEdit->appendPlainText(item);
  }
}

void ListWidget::OnBtnAppendClicked() {
  list_model_->insertRow(list_model_->rowCount());
  auto index = list_model_->index(list_model_->rowCount() - 1, 0);
  list_model_->setData(index, "new item", Qt::ItemDataRole::DisplayRole);
  ui->listView->setCurrentIndex(index);
}

void ListWidget::OnBtnRestoreClicked() {
  InitList();
}

void ListWidget::OnBtnInsertClicked() {
  auto index = ui->listView->currentIndex();
  if(!index.isValid()) return;

  list_model_->insertRow(index.row());
  list_model_->setData(index, "new item", Qt::ItemDataRole::DisplayRole);
  ui->listView->setCurrentIndex(index);
}


void ListWidget::OnBtnDelClicked() {
  auto index = ui->listView->currentIndex();
  if (!index.isValid()) return;
  list_model_->removeRow(index.row());
}

void ListWidget::OnBtnClearClicked() {
  list_model_->removeRows(0, list_model_->rowCount());
}

void ListWidget::OnBtnUpClicked() {
  auto currentIndex = ui->listView->currentIndex();
  if (!currentIndex.isValid() || currentIndex.row() == 0) return;

  list_model_->insertRow(currentIndex.row() - 1);
  currentIndex = list_model_->index(currentIndex.row() + 1, 0);
  auto insertIndex = list_model_->index(currentIndex.row() - 2, 0);
  auto data = std::move(list_model_->data(currentIndex, Qt::ItemDataRole::DisplayRole));
  list_model_->setData(insertIndex, data, Qt::ItemDataRole::DisplayRole);
  list_model_->removeRow(currentIndex.row());
  ui->listView->setCurrentIndex(insertIndex);

  OnListViewClicked(insertIndex);
}

void ListWidget::OnBtnDownClicked() {
  auto currentIndex = ui->listView->currentIndex();
  if (!currentIndex.isValid() || currentIndex.row() == list_model_->rowCount() - 1) return;

  list_model_->insertRow(currentIndex.row() + 2);
  auto insertIndex = list_model_->index(currentIndex.row() + 2, 0);
  auto data = std::move(list_model_->data(currentIndex, Qt::ItemDataRole::DisplayRole));
  list_model_->setData(insertIndex, data, Qt::ItemDataRole::DisplayRole);
  list_model_->removeRow(currentIndex.row());
  insertIndex = list_model_->index(insertIndex.row() - 1, 0);
  ui->listView->setCurrentIndex(insertIndex);

  OnListViewClicked(insertIndex);
}

void ListWidget::OnListViewClicked(const QModelIndex &index) {
  ui->labPos->setText(QString::asprintf("行: %d, 列: %d", index.row() + 1, index.column()));
}

void ListWidget::OnCbxEdtStateChanged(int state) {
  ui->listView->setEditTriggers(state ? QAbstractItemView::EditTrigger::DoubleClicked |
                                        QAbstractItemView::EditTrigger::SelectedClicked
                                      : QAbstractItemView::EditTrigger::NoEditTriggers);
}

void ListWidget::OnCbxAscStateChanged(int state) {
  list_model_->sort(0, state ? Qt::AscendingOrder : Qt::DescendingOrder);
}

void ListWidget::InitList() {
  QStringList list = {"item1", "item2", "item3", "item4", "item5"};
  list_model_->setStringList(list);
}

void ListWidget::InitConnection() {
  connect(ui->btnClearPlain, &QPushButton::clicked, ui->plainTextEdit, &QPlainTextEdit::clear);
  connect(ui->btnShowPlain, &QPushButton::clicked, this, &ListWidget::OnBtnShowPlainClicked);

  connect(ui->btnAppend, &QPushButton::clicked, this, &ListWidget::OnBtnAppendClicked);
  connect(ui->btnRestore, &QPushButton::clicked, this, &ListWidget::OnBtnRestoreClicked);
  connect(ui->btnInsert, &QPushButton::clicked, this, &ListWidget::OnBtnInsertClicked);
  connect(ui->btnDel, &QPushButton::clicked, this, &ListWidget::OnBtnDelClicked);
  connect(ui->btnClear, &QPushButton::clicked, this, &ListWidget::OnBtnClearClicked);
  connect(ui->btnUp, &QPushButton::clicked, this, &ListWidget::OnBtnUpClicked);
  connect(ui->btnDown, &QPushButton::clicked, this, &ListWidget::OnBtnDownClicked);

  connect(ui->listView, &QListView::clicked, this, &ListWidget::OnListViewClicked);
  connect(ui->cbxEdit, &QCheckBox::stateChanged, this, &ListWidget::OnCbxEdtStateChanged);
  connect(ui->cbxAsc, &QCheckBox::stateChanged, this, &ListWidget::OnCbxAscStateChanged);
}
