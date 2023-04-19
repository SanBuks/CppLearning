#include "widget.h"
#include "ui_widget.h"
#include <QMetaProperty>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    boy = new QPerson("王小明");
    boy->setProperty("score", 95);
    boy->setProperty("age", 10);
    boy->setProperty("sex", "Boy");
    connect(boy, &QPerson::ageChanged, this, &Widget::on_ageChanged);



    girl = new QPerson("张晓丽");
    girl->setProperty("score", 81);
    girl->setProperty("age", 20);
    girl->setProperty("sex", "Girl");
    connect(girl, &QPerson::ageChanged, this, &Widget::on_ageChanged);

    ui->sBoxBoyAge->setProperty("isBoy", true);
    ui->sBoxGirlAge->setProperty("isBoy", false);

    connect(ui->sBoxGirlAge, SIGNAL(valueChanged(int)),
            this, SLOT(on_spin_valueChanged(int)));
    connect(ui->sBoxBoyAge, SIGNAL(valueChanged(int)),
            this, SLOT(on_spin_valueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_ageChanged(int value)
{
    Q_UNUSED(value);
    auto *aPerson = qobject_cast<QPerson *>(sender());
    auto name = aPerson->property("name").toString();
    auto sex = aPerson->property("sex").toString();
    auto age = aPerson->age();
    auto str = name + "," + sex + QString::asprintf(", 年龄 = %d", age);
    ui->txtEdit->appendPlainText(str);
    // 缺少更新 QSpinBox值 且不触发信号的处理过程
}

void Widget::on_spin_valueChanged(int value)
{
    Q_UNUSED(value);

    auto *spinBox = qobject_cast<QSpinBox *>(sender());
    if (spinBox->property("isBoy").toBool()) {
        boy->setAge(value);
    } else {
        girl->setAge(value);
    }
}

void Widget::on_pushBtnIncBoyAge_clicked()
{
    boy->incAge();
}

void Widget::on_pushBtnIncGirlAge_clicked()
{
    girl->incAge();
}

void Widget::on_pushBtnClassInfo_clicked()
{
    const auto *meta = boy->metaObject();
    ui->txtEdit->clear();
    ui->txtEdit->appendPlainText("==元对象信息==");
    ui->txtEdit->appendPlainText(QString("类名称: %1").arg(meta->className()));
    ui->txtEdit->appendPlainText("property");
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
        QMetaProperty prop = meta->property(i);
        const auto *propName = prop.name();
        auto propValue = boy->property(propName).toString();
        ui->txtEdit->appendPlainText(
            QString("属性名称 = %1, 属性值 = %2").arg(propName).arg(propValue));
    }
    ui->txtEdit->appendPlainText("");
    ui->txtEdit->appendPlainText("==类附加信息==");
    for (int i = meta->classInfoOffset(); i< meta->classInfoCount(); ++i) {
        QMetaClassInfo classInfo = meta->classInfo(i);
        ui->txtEdit->appendPlainText(
            QString("Name = %1, Value = %2").arg(classInfo.name()).arg(classInfo.value()));
    }
}

