cmake_minimum_required(VERSION 3.16)
project(bidirectional_list)

add_subdirectory(inc)
add_subdirectory(gTests)
add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 LINKER_LANGUAGE CXX)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(${PROJECT_NAME} PUBLIC inc gtest_main)