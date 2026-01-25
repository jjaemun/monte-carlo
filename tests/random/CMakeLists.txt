# --random.

add_executable(
    rngtests
    rngtests.cpp
)

target_link_libraries(
    rngtests PRIVATE
    GTest::gtest_main
    mc
)

gtest_discover_tests(rngtests)


add_executable(
    disttests
    disttests.cpp
)

target_link_libraries(
    disttests PRIVATE
    GTest::gtest_main
    mc
)

gtest_discover_tests(disttests)
