#ifndef STRING_LIST_MODEL_VIEW__WIDGET_H_
#define STRING_LIST_MODEL_VIEW__WIDGET_H_

#include <QWidget>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
 Q_OBJECT

 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget() override;

 private slots:
  void on_btnTextClear_clicked();
  void on_btnTextImport_clicked();
  void on_btnIniList_clicked();
  void on_btnListClear_clicked();
  void on_btnListDelete_clicked();
  void on_btnListAppend_clicked();
  void on_btnListInsert_clicked();
  void on_listView_clicked(const QModelIndex &);
 private:
  Ui::Widget *ui;
  QStringListModel *string_list_model;

};

#endif //STRING_LIST_MODEL_VIEW__WIDGET_H_
