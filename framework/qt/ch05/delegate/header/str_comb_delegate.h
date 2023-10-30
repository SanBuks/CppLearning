#ifndef TABLE_HEADER_STR_COMB_DELEGATE_H_
#define TABLE_HEADER_STR_COMB_DELEGATE_H_

#include <QStyledItemDelegate>

class StrCombDelegate : public QStyledItemDelegate {
  Q_OBJECT
 public:
  explicit StrCombDelegate(QObject *parent = nullptr);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

  void setItems(const QStringList &list, bool editable);

 private:
  QStringList content_;
  bool editable_;
};

#endif
