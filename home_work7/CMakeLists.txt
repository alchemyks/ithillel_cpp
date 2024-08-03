cmake_minimum_required(VERSION 3.16.3)

add_compile_options(-std=c++11)

project(async_lambda VERSION 1.0.0 LANGUAGES CXX)

add_executable(async_lambda src/main.cpp)