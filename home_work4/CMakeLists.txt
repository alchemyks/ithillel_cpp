cmake_minimum_required(VERSION 3.16.3)

add_compile_options(-std=c++11)

project(shared_ptr VERSION 1.0.0 LANGUAGES CXX)

add_executable(shared_ptr src/main.cpp)