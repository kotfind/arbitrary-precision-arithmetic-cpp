#include "test_utils.hpp"
#include "Real.hpp"

TESTING_BEGIN

    TEST(addition)
        ASSERT_EQ(123_r + 145_r, 268_r)
    ENDTEST

TESTING_END
