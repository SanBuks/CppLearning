#include "widget.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget w;
  w.show();

  QString str("我是一个忍者");
  qDebug() << QString::asprintf("%d\n", str.indexOf("一"));
  return a.exec();
}
