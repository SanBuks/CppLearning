#ifndef TREE_WIDGET_MAIN_WINDOW_H_
#define TREE_WIDGET_MAIN_WINDOW_H_

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private slots:

  void on_dockWidget_visibilityChanged(bool visible);
  void on_dockWidget_topLevelChanged(bool topLevel);
  void on_actDockVisible_toggled(bool tog);
  void on_actDockFloat_triggered(bool checked);

  void on_actAddFolder_triggered();
  void on_actAddFiles_triggered();
  void on_actScanItems_triggered();
  void on_actDeleteItem_triggered();

  void on_treeWidget_currentItemChanged(QTreeWidgetItem *current,
                                        QTreeWidgetItem *previous);
  void on_actZoomFitH_triggered();
  void on_actZoomFitW_triggered();
  void on_actZoomRealSize_triggered();
  void on_actZoomIn_triggered();
  void on_actZoomOut_triggered();


 private:
  Ui::MainWindow *ui;
  QLabel *labFile;
  QPixmap pixmap;
  double pixRatio;
  enum treeItemType { itTopItem = 1, itGroupItem, itImageItem };
  enum treeColNum { colItem = 0, colItemType = 1 };

  void initTree();
  /***
   * 插入文件夹节点
   * @param parItem not null
   * @param dir folder name
   */
  void addFolderItem(QTreeWidgetItem *parItem, const QString &dir);
  /***
   * 插入多个文件节点
   * @param parItem not null
   * @param dir folder name
   */
  void addFileItems(QTreeWidgetItem *parItem, const QStringList &files_path);
  /**
   * 获取路径中的最后文件名
   * @param fullPathName
   */
  QString getFinalFolderName(const QString &fullPathName);

  /***
   * 改变节点标题
   * @param item
   */
  void changeItemCaption(QTreeWidgetItem *item);
  /***
   * 显示图片
   */
  void displayImage(QTreeWidgetItem *item);
};

#endif