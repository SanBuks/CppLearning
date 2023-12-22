cmake_minimum_required(VERSION 3.0)
project(dialog_basic)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

set(CMAKE_PREFIX_PATH "D:/DevelopTool/qt5.9/5.9.9")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(dialog_basic main.cc
               src/dialog.cc
               include/dialog.h)

target_link_libraries(dialog_basic
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets)