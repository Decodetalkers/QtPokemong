cmake_minimum_required(VERSION 3.5)

#project(neobutton VERSION 0.1 LANGUAGES CXX)

set(COMPONENT_NAME neobutton)

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
    ../../include/mywidgets/basewidgets/myoverlaywidget.h

    basewidgets/myoverlaywidget.cpp

    ../../include/mywidgets/models/pokemongmodel.h

    models/pokemongmodel.cpp

    ../../include/mywidgets/mybutton.h
    ../../include/mywidgets/myprogress.h
    ../../include/mywidgets/mypopupwindow.h
    ../../include/mywidgets/mydrawer.h
    ../../include/mywidgets/mybattlemap.h
    ../../include/mywidgets/mylinerbar.h
 
    mybutton.cpp
    mybutton_p.h
    mybutton_internal.h
    mybutton_internal.cpp

		
    myprogress.cpp
    myprogress_p.h
    myprogress_internal.h
    myprogress_internal.cpp


    mypopupwindow.cpp
    mypopupwindow_p.h
    mypopupwindow_internal.h
    mypopupwindow_internal.cpp

    mydrawer.cpp
    mybutton_p.h
    mydrawer_internal.h
    mydrawer_internal.cpp

    mybattlemap.cpp
    mybattlemap_p.h
    mybattlemap_internal.h
    mybattlemap_internal.cpp

    mylinerbar.cpp
    mylinerbar_p.h
    mylinerbar_internal.h
    mylinerbar_internal.cpp

)
set(RCC_FILES res.qrc)

add_library(${COMPONENT_NAME} SHARED
    ${PROJECT_SOURCES}
    ${RCC_FILES}
)

target_link_libraries(${COMPONENT_NAME} PRIVATE 
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Core
)
target_include_directories(${COMPONENT_NAME} PUBLIC
  ../../include/
)
install(TARGETS ${COMPONENT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
