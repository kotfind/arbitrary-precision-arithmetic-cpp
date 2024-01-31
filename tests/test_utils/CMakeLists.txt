add_library(test_utils SHARED)

target_sources(test_utils
    PUBLIC
        test_utils.hpp
    PRIVATE
        test_utils.cpp
)
