set(PINNAME pinit)
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
  ${PINNAME}
  dbusclient.cpp
  )
target_include_directories(${PINNAME} PUBLIC
  ../../include/
)
target_link_libraries(
  ${PINNAME} PRIVATE
  Qt5::Core
  Qt5::DBus
)
install(TARGETS ${PINNAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
