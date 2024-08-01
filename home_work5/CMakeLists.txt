cmake_minimum_required(VERSION 3.16.3)

add_compile_options(-std=c++11)

project(test_pcp VERSION 1.0.0 LANGUAGES CXX)

add_executable(test_pcp src/main.cpp)