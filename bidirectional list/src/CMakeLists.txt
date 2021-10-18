cmake_minimum_required(VERSION 3.16)

project(my_app LANGUAGES CXX)

#set(CMAKE_CXX_STANDART 17)
#set(CMAKE_CXX_STANDART_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)
                
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${PROJECT_NAME} PUBLIC myHeaders)
