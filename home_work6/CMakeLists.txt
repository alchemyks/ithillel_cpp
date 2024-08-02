cmake_minimum_required(VERSION 3.16.3)

add_compile_options(-std=c++11)

project(safety_vector VERSION 1.0.0 LANGUAGES CXX)

add_executable(safety_vector src/main.cpp)