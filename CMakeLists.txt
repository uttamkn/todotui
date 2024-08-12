cmake_minimum_required(VERSION 3.10)

project(TodoApp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCES src/Task.cpp src/TaskFileHandler.cpp src/TaskManager.cpp
            src/main.cpp)

add_executable(todo_app ${SOURCES})

target_include_directories(todo_app PRIVATE ${PROJECT_SOURCE_DIR}/src)
