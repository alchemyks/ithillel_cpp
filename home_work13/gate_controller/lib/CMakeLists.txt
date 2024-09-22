qt_add_library(gate STATIC gate.cpp)

target_link_libraries(gate PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_include_directories(gate INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
