#include <QApplication>
#include <QPushButton>
#include "list_widget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  ListWidget list_widget;
  list_widget.show();
  return QApplication::exec();
}
