#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // 创建应用程序
    Widget w;                    // 定义窗口并显示
    w.show();
    QList<int> list;
    return a.exec();             // 应用程序开始并处理事件
}
