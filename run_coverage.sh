#!/bin/bash

COVERAGE_BUILD_PRESET=g++-debug-coverage
COVERAGE_TEST_PRESET=g++-test-all-coverage

cmake --preset ${COVERAGE_BUILD_PRESET} && \
cmake --build --preset ${COVERAGE_BUILD_PRESET} && \
ctest --preset ${COVERAGE_TEST_PRESET} && \
lcov --directory ${ALGO_PATH}/build/${COVERAGE_BUILD_PRESET} --capture --output-file ${ALGO_PATH}/coverage.info --include "${ALGO_PATH}/algo/*" && \
genhtml --demangle-cpp -o ${ALGO_PATH}/coverage ${ALGO_PATH}/coverage.info
