cmake_minimum_required(VERSION 3.27.0)

set(This Testing)

set(Sources
    test.cpp
)

add_executable( ${This} ${Sources})

target_link_libraries( ${PROJECT_NAME} PUBLIC
    gtest_main
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)