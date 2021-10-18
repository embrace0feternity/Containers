cmake_minimum_required(VERSION 3.16)

project(myHeaders LANGUAGES CXX)

add_library(${PROJECT_NAME} list.h buffer.h)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")