add_library(real SHARED)

target_sources(real
    PUBLIC
        Real.hpp
    PRIVATE
        Real.cpp
)

set_target_properties(real
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
