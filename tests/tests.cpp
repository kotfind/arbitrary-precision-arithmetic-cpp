#include "test_utils.hpp"
#include "Real.hpp"
#include <sstream>

TESTING_BEGIN

    TEST(constructors)
        auto r = -12345.6789_r;
        ASSERT_EQ(r, Real(false, {9, 8, 7, 6, 5, 4, 3, 2, 1}, 4))
        ASSERT_EQ(r, Real(std::string("-12345.6789")))
        ASSERT_EQ(r, Real("-12345.6789"))
        ASSERT_EQ(r, Real(r))
    ENDTEST

    TEST(operator<<)
        std::stringstream ss;
        ss << -3268896530.2023705991_r;
        ASSERT_EQ(ss.str(), "-3268896530.2023705991")
    ENDTEST

    TEST(to_string)
        ASSERT_EQ(to_string(2735514744.3147754023_r), "2735514744.3147754023")
    ENDTEST

    TEST(operator=)
        auto r = -3149801828.307883561_r;
        r = 3278665592.315225564_r;
        ASSERT_EQ(r, 3278665592.315225564_r)
    ENDTEST

    TEST(operator+)
        // pos + pos
        ASSERT_EQ(655884368.1916515935_r + 2028270164.3974502332_r, 2684154532.5891018267_r)

        // pos + neg = neg
        ASSERT_EQ(1072373760.3187581626_r + -1449087661.1151335743_r, -376713900.7963754117_r)

        // pos + neg = pos
        ASSERT_EQ(2216446514.841234948_r + -1510618149.397088582_r, 705828365.444146366_r)

        // neg + pos = neg
        ASSERT_EQ(-664401958.2172599668_r + 128187116.1604717961_r, -536214842.0567881707_r);

        // neg + pos = pos
        ASSERT_EQ(-326734866.309236080_r + 3276936258.129337357_r, 2950201391.820101277_r)
    ENDTEST

    TEST(operator-)
        // pos - pos
        ASSERT_EQ(1037159214.4231653904_r - 3818859179.1667228530_r, -2781699964.7435574626_r)

        // pos - neg
        ASSERT_EQ(4107344621.1978250463_r - -1809649595.9059936163_r, 5916994217.1038186626_r)

        // neg - pos
        ASSERT_EQ(-3207383465.586899785_r - 1808578576.366508680_r, -5015962041.953408465_r)

        // neg - neg
        ASSERT_EQ(-1908527807.3535963337_r - -3406683692.7751901514_r, 1498155885.4215938177_r)
    ENDTEST

    TEST(unary operator-)
        // -pos
        ASSERT_EQ(-(1996684053.382433980_r), -1996684053.382433980_r)

        // -neg
        ASSERT_EQ(-(-929341728.2963807288_r), 929341728.2963807288_r)
    ENDTEST

    TEST(unary operator+)
        // +pos
        ASSERT_EQ(+(1869586195.288774109_r), 1869586195.288774109_r)

        // +neg
        ASSERT_EQ(+(-2315663850.1199077578_r), -2315663850.1199077578_r)
    ENDTEST

    TEST(operator*)
        // pos * pos
        ASSERT_EQ(4267606966.1668083999_r * 1791661283.1776658898_r, 7646106173100369718.7407155813_r)

        // pos * neg
        ASSERT_EQ(1862854725.2007241792_r * -1859396271.4144410261_r, -3463785130224999689.0914374205_r)

        // neg * pos
        ASSERT_EQ(-1108899885.3329591658_r * 2491825238.4242477003_r, -2763184721158421908.7793080863_r)

        // neg * neg
        ASSERT_EQ(3425610459.1888726404_r * 1531633440.3529749188_r, 5246779532916587185.6103580101_r)
    ENDTEST

    TEST(operator/)
        // pos / pos
        ASSERT_EQ(1457004858.905932176_r / 1829367322.404661332_r, 0.796452873_r)

        // pos / neg
        ASSERT_EQ(3767896258.2515432246_r / -3257215608.3294965432_r, -1.1567844169_r)

        // neg / pos
        ASSERT_EQ(-1763917393.1591958336_r / 3152471.1957309218_r, -559.5348168598_r)

        // neg / neg
        ASSERT_EQ(-2912284848.3152311157_r / -693.2752612911_r, 4200762.6853605398_r)
    ENDTEST

    TEST(operator>)
        // pos > pos
        ASSERT(100.123_r > 1.321_r)
        ASSERT(981.133_r > 981.121_r)

        // pos > neg
        ASSERT(0.001_r > -981.121_r)

        // neg > neg
        ASSERT(-0.021_r > -1000.000_r)
    ENDTEST

    TEST(operator<)
        ASSERT(1_r < 2_r)
    ENDTEST

    TEST(operator>=)
        ASSERT(100.123_r >= 1.321_r)
        ASSERT(100.123_r >= 100.123_r)
    ENDTEST

    TEST(operator<=)
        ASSERT(1_r <= 2_r)
        ASSERT(2_r <= 2_r)
    ENDTEST

    TEST(operator==)
        // pos == pos
        ASSERT(1106819323.1737542541_r == 1106819323.1737542541_r)

        // neg == neg
        ASSERT(-3776581856.1446168503_r == -3776581856.1446168503_r)
    ENDTEST

    TEST(operator!=)
        // pos != neg
        ASSERT(3776581856.1446168503_r != -3776581856.1446168503_r)

        // pos != pos
        ASSERT(781.9_r != 988.1_r)
    ENDTEST

    TEST(operator+=)
        auto r = 619432997.532047868_r;
        r += 148462106.161058610_r;
        ASSERT_EQ(r, 767895103.693106478_r);
    ENDTEST

    TEST(operator-=)
        auto r = 262965776.1721870976_r;
        r -= 2774727120.4051085300_r;
        ASSERT_EQ(r, -2511761344.2329214324_r);
    ENDTEST

    TEST(operator*=)
        auto r = 2550376691.2192346546_r;
        r *= 3739649502.1165462099_r;
        ASSERT_EQ(r, 9537514923527655386.0749364182_r);
    ENDTEST

    TEST(operator/=)
        auto r = 2875517532.4839150142_r;
        r /= 2529087980.3079742384_r;
        ASSERT_EQ(r, 1.1369780549_r);
    ENDTEST

    TEST(mul_sqrt)
        ASSERT_EQ((3436460146.310684651_r).mul_sqrt(3202969979.326705828_r), 3317661628.886493618_r)
        ASSERT_EQ((4527954651814088357.632214057_r).mul_sqrt(1.000000000_r), 2127899116.925914878_r)
    ENDTEST

TESTING_END
