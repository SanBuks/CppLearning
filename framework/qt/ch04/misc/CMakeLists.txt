cmake_minimum_required(VERSION 3.0)
project(misc)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS
             Core
             Gui
             Widgets
             REQUIRED)

add_executable(misc source/main.cpp
                    source/widget.cc
                    source/widget.ui
                    header/widget.h
                    resource.qrc)
target_include_directories(misc PUBLIC header)

target_link_libraries(misc
                      Qt5::Core
                      Qt5::Gui
                      Qt5::Widgets)
