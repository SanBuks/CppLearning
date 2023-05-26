#include <QApplication>
#include <QPushButton>

#include "include/dialog.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Dialog dialog;
  dialog.show();
  return QApplication::exec();
}
