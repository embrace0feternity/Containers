cmake_minimum_required(VERSION 3.16)
project(gTests)

include(FetchContent)
FetchContent_Declare(
  	googletest
  	URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  	${PROJECT_NAME}
  	AllTests.cpp
)
target_link_libraries(
  	${PROJECT_NAME}
  	PUBLIC myHeaders
  	gtest_main
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

