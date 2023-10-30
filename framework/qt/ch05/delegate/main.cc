#include <QApplication>
#include <QTextCodec>

#include "table_window.h"

int main(int argc, char *argv[]) {
  QTextCodec *codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForLocale(codec);
  QApplication a(argc, argv);

  TableWindow table_window;
  table_window.show();

  return QApplication::exec();
}
