cmake_minimum_required(VERSION 3.5)

project(plugina VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(PkgConfig REQUIRED)
pkg_check_modules(QGSettings REQUIRED gsettings-qt)

# Plugina
set(BIN_NAME1 myplugina)

set(PROJECT_SOURCES 
  demo.h
  demo.cpp
)
add_library(
  ${BIN_NAME1} SHARED 
  ${PROJECT_SOURCES}
)

target_include_directories(${BIN_NAME1} PUBLIC
  ../../../include/
)
target_link_libraries(
  ${BIN_NAME1} PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
)
# pluginb
#SET(RCC_FILES ../res.qrc)

set(BIN_NAME2 mypluginb)

add_library(
  ${BIN_NAME2} SHARED
  showmodel.cpp
  showmodel.h
)

target_include_directories(${BIN_NAME2} PUBLIC
  ../../../include/
)
target_link_libraries(
  ${BIN_NAME2} PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  neobutton
)

# pluginb
#SET(RCC_FILES ../res.qrc)

set(BIN_NAME3 mypluginc)

add_library(
  ${BIN_NAME3} SHARED
  savemodel.cpp
  savemodel.h
  ../theme-icons/theme-icons.qrc
)

target_include_directories(${BIN_NAME2} PUBLIC
  ../../../include/
  ${QGSettings_INCLUED_DIRS}
)
target_link_libraries(
  ${BIN_NAME3} PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  ${QGSettings_LIBRARIES}
  neobutton
)
