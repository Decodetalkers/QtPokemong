cmake_minimum_required(VERSION 3.7)

project(test VERSION 0.1 LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB_RECURSE SRCS "*.cpp")

find_package(Qt5 COMPONENTS Widgets Test DBus REQUIRED)
find_package(GTest REQUIRED)
add_executable(${PROJECT_NAME} ${SRCS} ${INTERFACES})

target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt5::Test
	Qt5::Widgets
	Qt5::DBus
	${GTEST_LIBRARIES}
	-lpthread
	-lm
	)

