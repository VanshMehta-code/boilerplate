cmake_minimum_required(VERSION 3.20)
project(boilerplate CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -O3 -march=native)
file(
  GLOB_RECURSE SOURCES 
  "src/*.cpp" 
  "lib/*.cpp"
)
target_include_directories(${PROJECT_NAME} PRIVATE 
  include 
  lib
)
add_executable(${PROJECT_NAME} ${SOURCES})
find_package(CURL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)