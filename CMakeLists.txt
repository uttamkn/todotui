cmake_minimum_required(VERSION 3.10)

project(Todotui VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCES src/Task.cpp src/TaskFileHandler.cpp src/TaskManager.cpp
            src/main.cpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(todotui ${SOURCES})

target_include_directories(todotui PRIVATE ${PROJECT_SOURCE_DIR}/include)
