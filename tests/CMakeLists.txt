
set(TEST_SRC src/core/ResultTests.cpp)

add_executable(tests ${TEST_SRC})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain core)

include(CTest)

# Catch.cmake is located in the extras directory
list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")
include(Catch)

catch_discover_tests(tests)