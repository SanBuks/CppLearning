#include <QApplication>
#include <QPushButton>
#include "file_widget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  FileWidget file_widget;
  file_widget.show();
  return QApplication::exec();
}
