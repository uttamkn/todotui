cmake_minimum_required(VERSION 3.10)

project(Todotui VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCES src/Task.cpp src/TaskRepository.cpp src/TaskFileHandler.cpp
            src/TaskManager.cpp src/TaskUI.cpp src/main.cpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

# ftxui
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main
  SOURCE_DIR ${CMAKE_BINARY_DIR}/external/ftxui)
FetchContent_MakeAvailable(ftxui)

# json
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
      SOURCE_DIR ${CMAKE_BINARY_DIR}/external/json)

FetchContent_MakeAvailable(json)

add_executable(todotui ${SOURCES})

target_link_libraries(
  todotui
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(todotui PRIVATE ${PROJECT_SOURCE_DIR}/include)
