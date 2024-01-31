add_subdirectory(test_utils)

add_executable(tests)

target_sources(tests PRIVATE tests.cpp)

target_link_libraries(tests PRIVATE
    test_utils
    real
)

target_include_directories(tests PRIVATE test_utils)

add_custom_target(test COMMAND tests)
