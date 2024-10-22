message(STATUS "Algo tests")

add_subdirectory(framework)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

file(GLOB_RECURSE TESTS ${TESTS_DIR}/*.cpp)

foreach(TEST_PATH IN LISTS TESTS)
    file(RELATIVE_PATH TEST_RELATIVE_PATH ${TESTS_DIR} ${TEST_PATH})
    get_filename_component(TEST_NAME ${TEST_RELATIVE_PATH} NAME_WE)
    get_filename_component(TEST_DIR ${TEST_RELATIVE_PATH} DIRECTORY)    
    set(TEST ${TEST_DIR}/${TEST_NAME})
    string(REPLACE "/" "_" TEST ${TEST})
    
    add_executable(${TEST} ${TEST_PATH})
    target_link_libraries(${TEST} algo framework)
    
    add_test(NAME ${TEST} COMMAND ${TEST})
endforeach()
