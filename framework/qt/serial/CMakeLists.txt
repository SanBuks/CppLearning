cmake_minimum_required(VERSION 3.0)
project(serial)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "D:/DevelopTool/qt/5.9.9/mingw53_32")

find_package(Qt5 COMPONENTS
             Core
             Gui
             Widgets
             SerialBus
             SerialPort
             REQUIRED)

add_executable(serial
               source/main.cc
               source/widget.cc
               header/widget.h
               source/widget.ui)
target_include_directories(serial PUBLIC header)
target_link_libraries(serial
                      Qt5::Core
                      Qt5::Gui
                      Qt5::Widgets
                      Qt5::SerialBus
                      Qt5::SerialPort)

if(WIN32)
  set(DEBUG_SUFFIX)
  if(MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
    set(DEBUG_SUFFIX "d")
  endif()
  set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
  if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
    set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
    if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
      set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
    endif()
  endif()
  if(EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E make_directory
                       "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                       "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                       "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
  endif()
  foreach(QT_LIB Core Gui Widgets)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                       "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                       "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
  endforeach(QT_LIB)
endif()
