#include <QApplication>
#include <QPushButton>

#include "dice_dialog.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  DiceDialog d;
  d.show();
  return QApplication::exec();
}
