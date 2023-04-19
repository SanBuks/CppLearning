#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->rBtnRed,   SIGNAL(clicked()), this, SLOT(setTextFontColour()));
    connect(ui->rBtnBlack, SIGNAL(clicked()), this, SLOT(setTextFontColour()));
    connect(ui->rBtnBlue,  SIGNAL(clicked()), this, SLOT(setTextFontColour()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_checkBoxUnderline_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setUnderline(checked);
    ui->plainTextEdit->setFont(font);
}

void Dialog::on_checkBoxItalic_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setItalic(checked);
    ui->plainTextEdit->setFont(font);
}

void Dialog::on_checkBoxBold_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setBold(checked);
    ui->plainTextEdit->setFont(font);
}

void Dialog::setTextFontColour()
{
   QPalette palette = ui->plainTextEdit->palette();
   if(ui->rBtnRed->isChecked()) {
       palette.setColor(QPalette::Text, Qt::red);
   } else if(ui->rBtnBlack->isChecked()) {
       palette.setColor(QPalette::Text, Qt::black);
   } else if(ui->rBtnBlue->isChecked()) {
       palette.setColor(QPalette::Text, Qt::blue);
   } else {
       palette.setColor(QPalette::Text, Qt::black);
   }
   ui->plainTextEdit->setPalette(palette);
}
