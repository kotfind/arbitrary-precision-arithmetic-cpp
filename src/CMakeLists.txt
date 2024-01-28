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
