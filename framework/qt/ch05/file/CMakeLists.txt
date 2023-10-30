cmake_minimum_required(VERSION 3.0)

project(file
        DESCRIPTION "MVC 模式"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "D:/DevelopTool/qt/5.9.9")
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_library(file_widget SHARED src/file_widget.cc header/file_widget.h)
target_link_libraries(file_widget PUBLIC Qt5::Widgets)
target_include_directories(file_widget PUBLIC header)

add_executable(file main.cc)
target_link_libraries(file PRIVATE file_widget)