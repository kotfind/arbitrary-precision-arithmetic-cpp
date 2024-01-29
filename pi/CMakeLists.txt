add_executable(pi main.cpp)

target_link_libraries(pi real)

set_target_properties(pi
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_custom_target(run COMMAND pi)
