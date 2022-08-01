#cmake_minimum_required(VERSION 3.7)

set(BIN_NAME test)
#project(test VERSION 0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#file(GLOB_RECURSE SRCS "*.cpp")

file(GLOB_RECURSE WIDGETS 
  ../src/game/pokemengwidgets/pokemengmap.cpp
  ../src/game/pokemengwidgets/pokemongtable.cpp
  ../src/game/models/pokemongmodel.h
  ../src/game/models/pokemongmodel.cpp
)
set(COMPONENT_SOURCES
    ../../include/mywidgets/basewidgets/myoverlaywidget.h

    ../src/components/basewidgets/myoverlaywidget.cpp

    ../../include/mywidgets/models/pokemongmodel.h

    ../src/components/models/pokemongmodel.cpp

    ../../include/mywidgets/mybutton.h
    ../../include/mywidgets/myprogress.h
    ../../include/mywidgets/mypopupwindow.h
    ../../include/mywidgets/mydrawer.h
    ../../include/mywidgets/mybattlemap.h
    ../../include/mywidgets/mylinerbar.h
 
    ../src/components/mybutton.cpp
    ../src/components/mybutton_p.h
    ../src/components/mybutton_internal.h
    ../src/components/mybutton_internal.cpp

		
    ../src/components/myprogress.cpp
    ../src/components/myprogress_p.h
    ../src/components/myprogress_internal.h
    ../src/components/myprogress_internal.cpp


    ../src/components/mypopupwindow.cpp
    ../src/components/mypopupwindow_p.h
    ../src/components/mypopupwindow_internal.h
    ../src/components/mypopupwindow_internal.cpp

    ../src/components/mydrawer.cpp
    ../src/components/mybutton_p.h
    ../src/components/mydrawer_internal.h
    ../src/components/mydrawer_internal.cpp

    ../src/components/mybattlemap.cpp
    ../src/components/mybattlemap_p.h
    ../src/components/mybattlemap_internal.h
    ../src/components/mybattlemap_internal.cpp

    ../src/components/mylinerbar.cpp
    ../src/components/mylinerbar_p.h
    ../src/components/mylinerbar_internal.h
    ../src/components/mylinerbar_internal.cpp
    ../src/components/res.qrc

)
find_package(Qt5 COMPONENTS Widgets Test DBus Network Concurrent REQUIRED)
find_package(GTest REQUIRED)
add_executable(${BIN_NAME} 
  ${WIDGETS} 
  ${INTERFACES}
	${COMPONENT_SOURCES}
  main.cpp 
  tst_mylinerbar.cpp
	tst_mydrawer.cpp
  tst_myprogress.cpp
  tst_mypopupwindow.cpp
  tst_mybattlemap.cpp
  tst_mybutton.cpp
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${BIN_NAME} PRIVATE -fprofile-instr-generate -ftest-coverage)
endif()
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${BIN_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
endif()
target_link_libraries(${BIN_NAME} PRIVATE
  Qt5::Test 
  Qt5::Widgets
  Qt5::DBus
  Qt5::Network
  Qt5::Concurrent
  #neobutton
  ${GTEST_LIBRARIES}
  -lpthread
  -lm
  -lgcov
  )
target_include_directories(${BIN_NAME} PUBLIC
  ../src/components/
  ../src/game/pokemengwidgets/
  ../src/game/models
  ../include/
)
