cmake_minimum_required(VERSION 3.16)

project(gate_controller LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
add_subdirectory(lib)

add_executable(gate_controller
 src/main.cpp
)
target_link_libraries(gate_controller PRIVATE
    gate
    Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS gate_controller
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
