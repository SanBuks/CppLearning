#include <QApplication>
#include <QPushButton>
#include "../include/painter_widget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  PainterWidget w;
  w.show();
  return QApplication::exec();
}
