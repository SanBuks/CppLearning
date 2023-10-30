#include "float_spin_delegate.h"

#include <QDoubleSpinBox>
#include <QDebug>

FloatSpinDelegate::FloatSpinDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *FloatSpinDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const {
  Q_UNUSED(option)
  Q_UNUSED(index)

  auto *editor = new QDoubleSpinBox(parent);
  editor->setFrame(false);
  editor->setMaximum(20000);
  editor->setMinimum(0);
  editor->setDecimals(2);
  return editor;
}

void FloatSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
  double value = index.model()->data(index, Qt::EditRole).toDouble();
  auto spin_box = dynamic_cast<QDoubleSpinBox *>(editor);
  spin_box->setValue(value);
}

void FloatSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
  auto spin_box = dynamic_cast<QDoubleSpinBox *>(editor);
  double value = spin_box->value();
  model->setData(index, QString::asprintf("%.2f", value), Qt::EditRole);
}

void FloatSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  Q_UNUSED(index)
  editor->setGeometry(option.rect);
}
