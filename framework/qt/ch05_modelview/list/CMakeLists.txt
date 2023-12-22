cmake_minimum_required(VERSION 3.26)
project(list)

project(list DESCRIPTION "QStringListModel" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "D:/DevelopTool/qt/5.9.9")
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_library(list_widget SHARED src/list_widget.cc header/list_widget.h)
target_link_libraries(list_widget PUBLIC Qt5::Widgets)
target_include_directories(list_widget PUBLIC header)

add_executable(list main.cc)
target_link_libraries(list PRIVATE list_widget)
