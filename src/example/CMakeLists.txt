set(EXAMPLE_NAME mybuttons)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
#
set(PROJECT_SOURCES
  main.cpp
  mainwindow.cpp
  mainwindow.h
)

add_executable(${EXAMPLE_NAME}
    ${PROJECT_SOURCES}
)

target_link_libraries(${EXAMPLE_NAME} PRIVATE 
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Core
  neobutton
)
target_include_directories(${EXAMPLE_NAME} PUBLIC
  ../../include/mywidgets/
)
