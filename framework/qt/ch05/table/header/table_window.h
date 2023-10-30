#ifndef TABLE_UI_TABLE_WINDOW_H_
#define TABLE_UI_TABLE_WINDOW_H_

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>

QT_BEGIN_NAMESPACE
namespace Ui { class TableWindow; }
QT_END_NAMESPACE

class TableWindow : public QMainWindow {
 Q_OBJECT

  static constexpr const int FixedRowCount = 10;
  static constexpr const int FixedColumnCount = 6;

 public:
  explicit TableWindow(QWidget *parent = nullptr);
  ~TableWindow() override;

 private slots:
  void OnItemChanged(const QModelIndex &current, const QModelIndex &previous);
  void OnOpenFile();
  void OnAppend();
  void OnInsert();
  void OnDelete();
  void OnBold(bool triggered);
  void OnLeft();
  void OnCenter();
  void OnRight();
  void OnShow();
  void OnSave();

 private:
  void InitConnection();
  void InitModelData(QStringList file_content);

  QLabel *lab_file_;
  QLabel *lab_pos_;
  QLabel *lab_cell_text_;

  QStandardItemModel *item_model_;
  QItemSelectionModel *item_selection_model_;

  Ui::TableWindow *ui;
};

#endif
