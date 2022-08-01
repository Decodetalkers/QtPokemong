set(BACKEND_NAME backend)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS DBus)
find_package(Qt5 REQUIRED COMPONENTS Core)

add_executable(
	${BACKEND_NAME}
	dbusserver.h
	dbusserver.cpp
	)
target_include_directories(${BACKEND_NAME} PUBLIC
	../../include/
)
target_link_libraries(
	${BACKEND_NAME} PRIVATE
	Qt5::Core
	Qt5::DBus
)
install(TARGETS ${BACKEND_NAME} DESTINATION bin)
