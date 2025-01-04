set(COVERAGE_COMPILE_FLAGS --coverage)
set(COVERAGE_LINK_FLAGS --coverage)

if(ALGO_COVERAGE)
    message(STATUS "Enable coverage")
    add_compile_options(${COVERAGE_COMPILE_FLAGS})
    add_link_options(${COVERAGE_LINK_FLAGS})
endif()
