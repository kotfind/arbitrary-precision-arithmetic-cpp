add_executable(tests tests.cpp)
add_custom_target(test COMMAND tests)

add_subdirectory(test_utils)

target_link_libraries(tests
    test_utils
    real
)

target_include_directories(tests PRIVATE test_utils)
