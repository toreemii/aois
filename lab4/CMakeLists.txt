cmake_minimum_required(VERSION 3.10)
project(HashTableProject)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0")

add_executable(run_tests tests.cpp)

add_executable(main_app main.cpp)