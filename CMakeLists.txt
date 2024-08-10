cmake_minimum_required(VERSION 3.10)

project(TodoApp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(todo_app src/main.cpp)

# To build the program(in the root directory).

# cmake -S . -B build

# cmake --build build
