cmake_minimum_required(VERSION 3.16)
project(inc LANGUAGES CXX)

add_library(${PROJECT_NAME} buffer.h list.h)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})