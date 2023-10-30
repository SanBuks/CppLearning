#include "str_comb_delegate.h"

#include <QComboBox>
#include <QDebug>

StrCombDelegate::StrCombDelegate(QObject *parent) : QStyledItemDelegate(parent), content_(), editable_(false) {}

QWidget *StrCombDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const {
  Q_UNUSED(option)
  Q_UNUSED(index)

  auto *editor = new QComboBox(parent);
  editor->setEditable(editable_);
  editor->addItems(content_);
  editor->setFrame(false);
  return editor;
}

void StrCombDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
  QString value = index.model()->data(index, Qt::EditRole).toString();
  auto combo_box = dynamic_cast<QComboBox *>(editor);
  combo_box->setCurrentText(value);
}

void StrCombDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
  auto combo_box = dynamic_cast<QComboBox *>(editor);
  QString value = combo_box->currentText();
  model->setData(index, value, Qt::EditRole);
}

void StrCombDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  Q_UNUSED(index)
  editor->setGeometry(option.rect);
}

void StrCombDelegate::setItems(const QStringList &list, bool editable) {
  content_ = list;
  editable_ = editable;
}
