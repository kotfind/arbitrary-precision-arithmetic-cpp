#include "Real.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>

const unsigned int Real::digit_size = 10;

Real::Real(bool is_positive, const std::vector<unsigned int>& digits, size_t precision)
  : is_positive(is_positive),
    digits(digits),
    precision(precision)
{
    if (this->digits.size() < this->precision) {
        this->digits.resize(precision);
    }
}

// FIXME: works only when digit_size == 10;
Real::Real(const std::string& num) {
    auto n = num.size();

    assert(n != 0);
    digits.reserve(n);

    size_t i = 0;

    if (num[i] == '-') {
        is_positive = false;
        ++i;
    } else {
        is_positive = true;
    }

    bool found_dot = false;
    for (; i < n; ++i) {
        char c = num[i];

        if (c == '.') {
            assert(!found_dot);
            found_dot = true;
            precision = 0;
            continue;
        }

        assert(isdigit(c));

        ++precision;
        digits.push_back(c - '0');
    }

    if (!found_dot) {
        std::cerr << "HERE";
        precision = 0;
    }

    std::reverse(digits.begin(), digits.end());
}

Real::Real(const Real& r)
  : is_positive(r.is_positive),
    digits(r.digits),
    precision(r.precision)
{}

// FIXME
std::ostream& operator<<(std::ostream& out, const Real& r) {
    if (!r.is_positive) {
        out << "-";
    }

    for (int i = r.digits.size() - 1; i >= 0; --i) {
        out << r.digits[i];
        if (i == r.precision) {
            out << ".";
        }
    }
    return out;
}

void Real::add_digits(
    std::vector<unsigned int>& lhs,
    const std::vector<unsigned int>& rhs
) {
    auto n = std::max(lhs.size(), rhs.size());
    lhs.resize(n, 0);

    unsigned int carry = 0;
    for (size_t i = 0; i < n; ++i) {
        auto val = lhs[i] + rhs[i] + carry;
        carry = val / digit_size;
        lhs[i] = val % digit_size;
    }

    while (carry != 0) {
        lhs.push_back(carry % digit_size);
        carry /= digit_size;
    }
}

void Real::sub_digits(
    std::vector<unsigned int>& lhs,
    const std::vector<unsigned int>& rhs
) {
    assert(lhs.size() >= rhs.size());
    auto n = rhs.size();

    unsigned int carry = 0;
    for (size_t i = 0; i < n; ++i) {
        if (lhs[i] < rhs[i] + carry) {
            lhs[i] = lhs[i] + digit_size - rhs[i] - carry;
            carry = 1;
        } else {
            lhs[i] = lhs[i] - rhs[i] - carry;
            carry = 0;
        }
    }

    for (size_t i = n; carry != 0; ++i) {
        assert(i < lhs.size());
        if (lhs[i] == 0) {
            lhs[i] = digit_size - carry;
        } else {
            lhs[i] = lhs[i] - carry;
            carry = 0;
        }
    }
}

size_t Real::count_non_zero_digits(const std::vector<unsigned int>& digits) {
    assert(digits.size() != 0);
    for (size_t i = digits.size() - 1; i != static_cast<size_t>(-1); --i) {
        if (digits[i] != 0) {
            return i;
        }
    }
    return 0;
}

int Real::cmp_digits(
    const std::vector<unsigned int>& lhs,
    const std::vector<unsigned int>& rhs
) {
    auto n = count_non_zero_digits(lhs);
    auto m = count_non_zero_digits(rhs);
    if (n < m) {
        return -1;
    }
    if (n > m) {
        return 1;
    }

    for (size_t i = n - 1; i != static_cast<size_t>(-1); --i) {
        if (lhs[i] < rhs[i]) {
            return -1;
        }
        if (lhs[i] > rhs[i]) {
            return 1;
        }
    }

    return 0;
}
 
Real& Real::operator=(const Real& r) {
    is_positive = r.is_positive;
    digits = r.digits;
    precision = r.precision;
    return *this;
}

Real& Real::operator+=(const Real& r) {
    assert(precision == r.precision);

    if (is_positive == r.is_positive) {
        add_digits(digits, r.digits);
    } else {
        auto dig_cmp = cmp_digits(digits, r.digits);

        if (dig_cmp == 0) {
            digits.assign(precision, 0);
            is_positive = true;
            return *this;
        }

        if (dig_cmp == -1) {
            is_positive = r.is_positive;

            Real tmp(*this);
            *this = r;
        }
        sub_digits(digits, r.digits);
    }

    // TODO: clear leading zeros
    return *this;
}

Real& Real::operator-=(const Real& r) {
    assert(precision == r.precision);
    return operator+=(-r);
    return *this;
}

// Real& Real::operator*=(const Real& r) {
//     assert(precision == r.precision);
// }
// 
// Real& Real::operator/=(const Real& r) {
//     assert(precision == r.precision);
// }

Real Real::operator-() const {
    return Real(!is_positive, digits, precision);
}

Real Real::operator+() const {
    return Real(*this);
}

Real operator+(const Real& lhs, const Real& rhs) {
    Real ans(lhs);
    ans += rhs;
    return ans;
}

Real operator-(const Real& lhs, const Real& rhs) {
    Real ans(lhs);
    ans -= rhs;
    return ans;
}

Real operator*(const Real& lhs, const Real& rhs) {
    Real ans(lhs);
    ans *= rhs;
    return ans;
}

Real operator/(const Real& lhs, const Real& rhs) {
    Real ans(lhs);
    ans /= rhs;
    return ans;
}
