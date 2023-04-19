cmake_minimum_required(VERSION 3.0)
project(calc_spinbox)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS
             Core
             Gui
             Widgets
             REQUIRED)

add_executable(calc_spinbox
               source/main.cpp
               source/widget.cc
               header/widget.h
               source/widget.ui)

target_include_directories(calc_spinbox PUBLIC header)

target_link_libraries(calc_spinbox
                      Qt5::Core
                      Qt5::Gui
                      Qt5::Widgets)
