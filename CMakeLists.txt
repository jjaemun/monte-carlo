cmake_minimum_required(VERSION 3.20..3.29)
project(monte-carlo)


set(CMAKE_CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG master
)

FetchContent_MakeAvaliable(eigen)


add_subdirectory(src)


option(ENABLE_TEST_BUILDS "Enable building tests." OFF)

if(ENABLE_TEST_BUILDS) 
    enable_testing()
    add_subdirectory(tests)
endif()


