#ifndef TABLE_WIDGET_MAIN_WINDOW_H_
#define TABLE_WIDGET_MAIN_WINDOW_H_

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QLabel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 public slots:
  void on_btnSetHeader_clicked();
  void on_btnSetRows_clicked();
  void on_chkBoxRowColor_clicked(bool checked);
  void on_btnIniData_clicked();
  void on_btnInsertRow_clicked();
  void on_btnAppendRow_clicked();
  void on_btnDelCurRow_clicked();
  void on_btnAutoHeght_clicked();
  void on_btnAutoWidth_clicked();
  void on_btnReadToEdit_clicked();

 private:
  void CreateARow(int row, const QString &name, const QString &sex, QDate date,
                  const QString &ethnicity, bool is_pm, int score);

  // 单元格类型
  enum CellType { CTName = 1000, CTSex, CTBirth, CTEthnicity, CTPM, CTScore };
  // 字段列号
  enum FieldColNum {COLName, COLSex, COLBirth, COLEthnicity, COLPM, COLScore };

  static constexpr const unsigned long long kStuId = 201605010000u;

  Ui::MainWindow *ui;
  QLabel *labCellIndex;
  QLabel *labCellType;
  QLabel *labStudID;
};

#endif
