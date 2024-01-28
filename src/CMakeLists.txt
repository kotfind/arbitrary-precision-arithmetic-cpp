add_library(real SHARED)

target_sources(real
    PUBLIC
        Real.hpp
    PRIVATE
        Real.cpp
)

add_executable(real_bin main.cpp)
add_custom_target(run COMMAND real_bin)

target_link_libraries(real_bin real)

set_target_properties(real_bin real
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
