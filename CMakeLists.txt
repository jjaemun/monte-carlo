cmake_minimum_required(VERSION 3.20..3.29)
project(monte-carlo)


set(CMAKE_CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(eigen)

FetchContent_Declare(
    eigenrand
    GIT_REPOSITORY https://github.com/bab2min/EigenRand.git
    GIT_TAG main
)

set(EIGENRAND_BUILD_TEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(eigenrand)


add_library(monte-carlo INTERFACE)
target_include_directories(
    monte-carlo INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    monte-carlo INTERFACE
    Eigen3::Eigen
    EigenRand::EigenRand
)


option(ENABLE_TEST_BUILDS "Enable building tests." OFF)

if(ENABLE_TEST_BUILDS) 
    enable_testing()
    add_subdirectory(tests)
endif()


