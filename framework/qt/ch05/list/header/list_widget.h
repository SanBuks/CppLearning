#ifndef LIST_UI_LIST_WIDGET_H_
#define LIST_UI_LIST_WIDGET_H_

#include <QWidget>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class ListWidget; }
QT_END_NAMESPACE

class ListWidget : public QWidget {
 Q_OBJECT

 public:
  explicit ListWidget(QWidget *parent = nullptr);
  ~ListWidget() override;

 private slots:
  void OnBtnShowPlainClicked();       // 在 PlainTextEdit 显示 list 内容

  void OnBtnAppendClicked();          // 在 List 追加
  void OnBtnRestoreClicked();         // 在 List 恢复
  void OnBtnInsertClicked();          // 在 List 增加
  void OnBtnDelClicked();             // 在 List 删除
  void OnBtnClearClicked();           // 在 List 清空
  void OnBtnUpClicked();              // 上移 Item
  void OnBtnDownClicked();            // 下移 Item

  void OnListViewClicked(const QModelIndex &index);  // 显示坐标
  void OnCbxEdtStateChanged(int state);  // 可修改状态 改变
  void OnCbxAscStateChanged(int state);  // 升序状态 改变


 private:
  void InitList();              // 初始化列表
  void InitConnection();        // 初始化信号槽连接

  QStringListModel *list_model_;

  Ui::ListWidget *ui;
};

#endif
