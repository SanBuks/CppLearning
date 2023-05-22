cmake_minimum_required(VERSION 3.0)
project(table_widget)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

set(CMAKE_PREFIX_PATH "D:\\DevelopTool\\qt\\5.9.9\\mingw53_32")

find_package(Qt5 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_library(main_window SHARED src/main_window.cc include/main_window.h)
target_include_directories(main_window PUBLIC include)
target_link_libraries(main_window Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(table_widget
  src/main.cc
  source.qrc)

target_include_directories(table_widget PRIVATE include)
target_link_libraries(table_widget main_window Qt5::Core Qt5::Gui Qt5::Widgets)