cmake_minimum_required(VERSION 3.5)

project(neobutton VERSION 0.1 LANGUAGES CXX)

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

    ../../include/mywidgets/mybutton.h
    ../../include/mywidgets/myprogress.h
    ../../include/mywidgets/mypopupwindow.h
		../../include/mywidgets/mydrawer.h
		../../include/mywidgets/mybattlemap.h
 
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

)
set(RCC_FILES res.qrc)

add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCES}
		${RCC_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Core
)
target_include_directories(${PROJECT_NAME} PUBLIC
	../../include/mywidgets/
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
