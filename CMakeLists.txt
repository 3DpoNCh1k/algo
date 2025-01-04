cmake_minimum_required(VERSION 3.13)

project(algo)

include(cmake/CompileOptions.cmake)
include(cmake/Development.cmake)
include(cmake/Sanitize.cmake)
include(cmake/Coverage.cmake)

add_subdirectory(algo)

option(ALGO_TESTS "Build algo tests" OFF)

if(ALGO_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
