#include "dialog.h"
#include <QHBoxLayout>

void Dialog::iniUI()
{
    chkBoxUnder = new QCheckBox(tr("Underline"));
    chkBoxItalic= new QCheckBox(tr("Italic"));
    chkBoxBold = new QCheckBox(tr("Bold"));
    QHBoxLayout *HLay1 = new QHBoxLayout;
    HLay1->addWidget(chkBoxUnder);
    HLay1->addWidget(chkBoxItalic);
    HLay1->addWidget(chkBoxBold);

    rBtnBlack = new QRadioButton(tr("Black"));
    rBtnRed = new QRadioButton(tr("Red"));
    rBtnBlue = new QRadioButton(tr("Blue"));
    QHBoxLayout *HLay2 = new QHBoxLayout;
    HLay2->addWidget(rBtnBlack);
    HLay2->addWidget(rBtnRed);
    HLay2->addWidget(rBtnBlue);
    rBtnBlack->setChecked(true);

    btnOK = new QPushButton(tr("OK"));
    btnCancel= new QPushButton(tr("Cancel"));
    btnClose= new QPushButton(tr("Close"));
    QHBoxLayout *HLay3 = new QHBoxLayout;
    HLay3->addStretch();
    HLay3->addWidget(btnOK);
    HLay3->addWidget(btnCancel);
    HLay3->addStretch();
    HLay3->addWidget(btnClose);

    txtEdit = new QPlainTextEdit;
    txtEdit->setPlainText(tr("hello"));
    QFont font = txtEdit->font();
    font.setPointSize(20);
    txtEdit->setFont(font);

    QVBoxLayout *VLay = new QVBoxLayout;
    VLay->addLayout(HLay1);
    VLay->addLayout(HLay2);
    VLay->addWidget(txtEdit);
    VLay->addLayout(HLay3);
    setLayout(VLay);
}

void Dialog::iniSignalSlots()
{
    connect(rBtnBlack, SIGNAL(clicked()), this, SLOT(setTextFontColour()));
    connect(rBtnRed, SIGNAL(clicked()), this, SLOT(setTextFontColour()));
    connect(rBtnBlue, SIGNAL(clicked()), this, SLOT(setTextFontColour()));

    connect(chkBoxUnder, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxUnder(bool)));
    connect(chkBoxItalic, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxItalic(bool)));
    connect(chkBoxBold, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxBold(bool)));

    connect(btnOK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));
    QMetaObject::connectSlotsByName(this);
}

void Dialog::setTextFontColour()
{
   QPalette palette = txtEdit->palette();
   if(rBtnRed->isChecked()) {
       palette.setColor(QPalette::Text, Qt::red);
   } else if(rBtnBlack->isChecked()) {
       palette.setColor(QPalette::Text, Qt::black);
   } else if(rBtnBlue->isChecked()) {
       palette.setColor(QPalette::Text, Qt::blue);
   } else {
       palette.setColor(QPalette::Text, Qt::black);
   }
   txtEdit->setPalette(palette);
}

void Dialog::on_chkBoxUnder(bool checked)
{
    QFont font = txtEdit->font();
    font.setUnderline(checked);
    txtEdit->setFont(font);
}
void Dialog::on_chkBoxItalic(bool checked)
{
    QFont font = txtEdit->font();
    font.setItalic(checked);
    txtEdit->setFont(font);
}
void Dialog::on_chkBoxBold(bool checked)
{
    QFont font = txtEdit->font();
    font.setBold(checked);
    txtEdit->setFont(font);
}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    iniUI();
    iniSignalSlots();
    setWindowTitle("Dialog_From_Code");
}

Dialog::~Dialog()
{
}

