cmake_minimum_required(VERSION 3.5)

project(pokemongbattle VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS DBus)
find_package(PkgConfig REQUIRED)

pkg_check_modules(QGSettings REQUIRED gsettings-qt)

file(GLOB HEADER "*.h")
file(GLOB RSOURCE "*.cpp")
file(GLOB POKEMONG "pokemengwidgets/*")
set(POKEMONGMODEL
  models/pokemongmodel.h
  models/pokemongmodel.cpp
)
SET(RCC_FILES res.qrc)

add_executable(
  ${PROJECT_NAME}
  ${HEADER}
  ${RSOURCE}
  ${POKEMONG}
  ${RCC_FILES}
  ${POKEMONGMODEL}
)


add_subdirectory(plugins)
target_include_directories(${PROJECT_NAME} PUBLIC
  ../../include/
  models/
  ${QGSettings_INCLUED_DIRS}
)
target_link_libraries(
  ${PROJECT_NAME} PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::DBus
  ${QGSettings_LIBRARIES}
  neobutton
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE

)

#bin
install(TARGETS ${BIN_NAME} DESTINATION bin)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(myplugin)
endif()
