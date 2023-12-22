#ifndef TABLE_HEADER_FLOAT_SPIN_DELEGATE_H_
#define TABLE_HEADER_FLOAT_SPIN_DELEGATE_H_

#include <QStyledItemDelegate>

class FloatSpinDelegate : public QStyledItemDelegate {
  Q_OBJECT
 public:
  explicit FloatSpinDelegate(QObject *parent = nullptr);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif
