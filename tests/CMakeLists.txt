cmake_minimum_required(VERSION 3.7)

project(test VERSION 0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB_RECURSE SRCS "*.cpp")

file(GLOB_RECURSE WIDGETS 
  ../src/game/pokemengwidgets/pokemengmap.cpp
  ../src/game/pokemengwidgets/pokemongtable.cpp
)

find_package(Qt5 COMPONENTS Widgets Test DBus Network Concurrent REQUIRED)
find_package(GTest REQUIRED)
add_executable(${PROJECT_NAME} ${SRCS} ${WIDGETS} ${INTERFACES})

target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt5::Test 
  Qt5::Widgets
  Qt5::DBus
  Qt5::Network
  Qt5::Concurrent
  neobutton
  ${GTEST_LIBRARIES}
  -lpthread
  -lm
  )
target_include_directories(${PROJECT_NAME} PUBLIC
  ../src/game/pokemengwidgets/
  ../include/
)
