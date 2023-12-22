cmake_minimum_required(VERSION 3.26)
project(event_default)

project(event_default DESCRIPTION "QEvent" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "D:/DevelopTool/qt/5.9.9")
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_library(widget SHARED src/widget.cc header/widget.h )
target_link_libraries(widget PUBLIC Qt5::Widgets)
target_include_directories(widget PUBLIC header)

add_executable(event_default main.cc res.qrc)
target_link_libraries(event_default PRIVATE widget)