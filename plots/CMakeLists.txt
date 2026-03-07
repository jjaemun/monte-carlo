# --testing.

include(FetchContent)
FetchContent_Declare(
    matplot
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
    GIT_TAG master
)

FetchContent_MakeAvailable(matplot)


set(
    directories
    distributions
    simulators
)

foreach(directory ${directories})

    # --scalable.

    add_subdirectory(${directory})
endforeach()
