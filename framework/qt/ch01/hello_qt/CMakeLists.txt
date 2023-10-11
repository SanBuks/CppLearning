cmake_minimum_required(VERSION 3.5)

project(hello_qt
        DESCRIPTION "CMAKE 基础项目构建 & QtDesigner 基本使用"
        LANGUAGES CXX)

# 设置语言标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 加入 build 与 project 目录 到 include 路径中
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置自定义 Qt 安装路径 /mingw53_32
set(CUSTOM_QT_INSTALL_PATH "D:/DevelopTool/qt/5.9.9")
# 指定 UIC 路径
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

set(CMAKE_AUTOMOC ON) # 自动采用 MOC 处理源文件
set(CMAKE_AUTOUIC ON) # 自动采用 UIC 处理.ui文件
set(CMAKE_AUTORCC ON) # 自动采用 RCC 处理.qrc文件

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)  # 引用 Qt 模块

# 主界面
add_library(main_window SHARED
            src/mainwindow.cc
            header/mainwindow.h) # MOC 原因需要包含头文件
target_link_libraries(main_window PUBLIC Qt5::Widgets) # 引用 Qt 库
target_include_directories(main_window PUBLIC header)  # 指定 头文件夹

# 主程序
add_executable(hello_qt main.cc)
target_link_libraries(hello_qt PRIVATE main_window)