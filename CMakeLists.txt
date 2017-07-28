cmake_minimum_required(VERSION 3.7)
project(STIL_Interpreter)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp)

add_executable(STIL_Interpreter ${SOURCE_FILES})