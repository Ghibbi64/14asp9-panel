cmake_minimum_required(VERSION 3.16)
project(panel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release)
endif()

include(FetchContent)
set(FTXUI_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(FTXUI_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(FTXUI_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v7.0.3
)
FetchContent_MakeAvailable(ftxui)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS
  src/*.cpp
)

add_executable(14asp9-panel main.cpp ${SRCS})

target_include_directories(14asp9-panel PRIVATE include)
target_compile_options(14asp9-panel PRIVATE -Wall)
target_link_libraries(14asp9-panel PRIVATE
  ftxui::screen ftxui::dom ftxui::component)