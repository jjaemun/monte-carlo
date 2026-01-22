cmake_minimum_required(VERSION 3.20..3.29)
project(monte-carlo)


set(CMAKE_CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)


add_library(mc INTERFACE)
target_include_directories(
    mc INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

option(ENABLE_TEST_BUILDS "Enable building tests." OFF)

if(ENABLE_TEST_BUILDS) 
    enable_testing()
    add_subdirectory(tests)
endif()


