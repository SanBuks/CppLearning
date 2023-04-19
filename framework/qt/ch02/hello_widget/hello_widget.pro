# hello_widget
# 1. 熟悉 pro 文件结构
# 2. 简单了解信号槽和类继承关系
# 3. 简单了解 main 函数
# 4. 熟悉 Ui_Widget 类与 Widget 类的关系

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

TARGET = hello_widget

SOURCES += \
    main.cpp \
    widget.cpp
HEADERS += \
    widget.h
FORMS += \
    widget.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
