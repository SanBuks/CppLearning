cmake_minimum_required(VERSION 3.26)
project(table)

project(table DESCRIPTION "QStandardItemModel" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "D:/DevelopTool/qt/5.9.9")
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_library(table_window SHARED src/table_window.cc header/table_window.h )
target_link_libraries(table_window PUBLIC Qt5::Widgets)
target_include_directories(table_window PUBLIC header)

add_executable(table main.cc src.qrc)
target_link_libraries(table PRIVATE table_window)
