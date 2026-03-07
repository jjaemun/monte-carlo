# --simulators.
add_executable(
    gbm
    gbm.cpp
)

target_link_libraries(
    gbm PRIVATE
    matplot
    mc
)


add_executable(
    abm
    abm.cpp
)

target_link_libraries(
    abm PRIVATE
    matplot
    mc
)
