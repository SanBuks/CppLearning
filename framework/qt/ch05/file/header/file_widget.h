//
// Created by San on 2023/10/23.
//

#ifndef FILE_UI_FILE_WIDGET_H_
#define FILE_UI_FILE_WIDGET_H_

#include <QWidget>
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class FileWidget; }
QT_END_NAMESPACE

class FileWidget : public QWidget {
 Q_OBJECT

 public:
  explicit FileWidget(QWidget *parent = nullptr);
  ~FileWidget() override;

  void onTreeViewClicked(const QModelIndex &index);

 private:
  Ui::FileWidget *ui;

  QFileSystemModel *file_system_model_;
};

#endif //FILE_UI_FILE_WIDGET_H_
