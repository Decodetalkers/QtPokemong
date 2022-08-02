set(GAMENAME pokemongbattle)
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
file(GLOB POKEMONG "pokemongwidgets/*")
#set(POKEMONGMODEL
#  models/pokemongmodel.h
#  models/pokemongmodel.cpp
#)
SET(RCC_FILES res.qrc)

add_executable(
  ${GAMENAME}
  ${HEADER}
  ${RSOURCE}
  ${POKEMONG}
  ${RCC_FILES}
)

add_definitions(-DPLUGINDIR="/usr/share/pokemongbattle/plugins")

add_subdirectory(plugins)
target_include_directories(${GAMENAME} PUBLIC
  ../../include/
  ${QGSettings_INCLUED_DIRS}
)
target_link_libraries(
  ${GAMENAME} PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::DBus
  ${QGSettings_LIBRARIES}
  neobutton
)
#bin
install(TARGETS ${GAMENAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(myplugin)
endif()
