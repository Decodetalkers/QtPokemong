cmake_minimum_required(VERSION 3.5)

project(backend VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS DBus)
find_package(Qt5 REQUIRED COMPONENTS Core)

add_executable(
	${PROJECT_NAME}
	dbusserver.h
	dbusserver.cpp
	)
target_include_directories(${PROJECT_NAME} PUBLIC
	../include/
)
target_link_libraries(
	${PROJECT_NAME} PRIVATE
	Qt5::Core
	Qt5::DBus
)
install(TARGETS ${BIN_NAME} DESTINATION bin)
