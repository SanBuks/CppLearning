cmake_minimum_required(VERSION 3.26)
project(table)

project(table DESCRIPTION "QStyledItemDelegate" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "D:/DevelopTool/qt/5.9.9")
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_library(float_spin_delegate SHARED src/float_spin_delegate.cc header/float_spin_delegate.h)
target_include_directories(float_spin_delegate PUBLIC header)
target_link_libraries(float_spin_delegate PUBLIC Qt5::Widgets)

add_library(str_comb_delegate SHARED src/str_comb_delegate.cc header/str_comb_delegate.h)
target_include_directories(str_comb_delegate PUBLIC header)
target_link_libraries(str_comb_delegate PUBLIC Qt5::Widgets)

add_library(table_window SHARED src/table_window.cc header/table_window.h )
target_include_directories(table_window PUBLIC header)
target_link_libraries(table_window PUBLIC
                      float_spin_delegate
                      str_comb_delegate
                      Qt5::Widgets)

add_executable(table main.cc src.qrc)
target_link_libraries(table PRIVATE table_window)
