#ifndef DIALOG_CUSTOM_FORMS_DIALOG_SIZE_H_
#define DIALOG_CUSTOM_FORMS_DIALOG_SIZE_H_

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class DialogSize; }
QT_END_NAMESPACE

class DialogSize : public QDialog {
 Q_OBJECT

 public:
  explicit DialogSize(QWidget *parent = nullptr);
  ~DialogSize() override;

 private:
  Ui::DialogSize *ui;
};

#endif
