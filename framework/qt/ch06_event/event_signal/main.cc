#include <QApplication>

#include "widget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget widget;
  widget.show();
  return QApplication::exec();
}
