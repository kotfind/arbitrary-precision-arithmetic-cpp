#include "Real.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstring>
#include <sstream>

const unsigned int Real::DIGIT_MAX = 10;

Real::Real(bool is_positive, const std::vector<unsigned int>& digits, size_t precision)
  : is_positive(is_positive),
    digits(digits),
    precision(precision)
{}

Real::Real(const std::string& num)
  : Real(num.c_str())
{}

Real::Real(const char* num) {
    static_assert(DIGIT_MAX == 10);

    auto n = strlen(num);

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
        precision = 0;
    }

    std::reverse(digits.begin(), digits.end());
}

Real::Real(const Real& r)
  : is_positive(r.is_positive),
    digits(r.digits),
    precision(r.precision)
{}

Real Real::with_precision(size_t new_precision) const {
    if (new_precision == precision) {
        return Real(*this);
    }

    std::vector<unsigned int> new_digits = digits;
    shift_digits(new_digits, new_precision - precision);

    return Real(is_positive, new_digits, new_precision);
}

std::ostream& operator<<(std::ostream& out, const Real& r) {
    if (r.digits.size() == 0) {
        out << 0;
        return out;
    }

    if (!r.is_positive) {
        out << "-";
    }

    for (size_t i = std::max(r.digits.size() - 1, r.precision); i != static_cast<size_t>(-1); --i) {
        out << (i < r.digits.size() ? r.digits[i] : 0);
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
        auto val = lhs[i] + (i < rhs.size() ? rhs[i] : 0) + carry;
        carry = val / DIGIT_MAX;
        lhs[i] = val % DIGIT_MAX;
    }

    while (carry != 0) {
        lhs.push_back(carry % DIGIT_MAX);
        carry /= DIGIT_MAX;
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
            lhs[i] = lhs[i] + DIGIT_MAX - rhs[i] - carry;
            carry = 1;
        } else {
            lhs[i] = lhs[i] - rhs[i] - carry;
            carry = 0;
        }
    }

    for (size_t i = n; carry != 0; ++i) {
        assert(i < lhs.size());
        if (lhs[i] == 0) {
            lhs[i] = DIGIT_MAX - carry;
        } else {
            lhs[i] = lhs[i] - carry;
            carry = 0;
        }
    }
}

void Real::shift_digits(
    std::vector<unsigned int>& lhs,
    int shift
) {
    if (shift > 0) {
        std::vector<unsigned int> zeros(shift, 0);
        lhs.insert(lhs.begin(), zeros.begin(), zeros.end());
    } else {
        shift *= -1;
        assert(lhs.size() >= shift);
        lhs.erase(lhs.begin(), lhs.begin() + shift);
    }
}

void Real::mul_digits(
    std::vector<unsigned int>& lhs,
    const std::vector<unsigned int>& rhs
) {
    auto n = lhs.size();
    auto m = rhs.size();
    assert(n != 0);
    assert(m != 0);

    std::vector<unsigned int> ans;

    for (size_t j = 0; j < m; ++j) {
        auto row = lhs;
        for (size_t i = 0; i < n; ++i) {
            row[i] *= rhs[j];
        }
        shift_digits(row, j);
        add_digits(ans, row);
    }

    lhs = ans;
}
 
void Real::div_digits(
    std::vector<unsigned int>& lhs,
    const std::vector<unsigned int>& rhs
) {
    if (cmp_digits(lhs, rhs) == CmpValue::LESS) {
        lhs = {};
        return;
    }

    size_t max_shift = 0;
    while (true) {
        auto shifted = rhs;
        shift_digits(shifted, max_shift);

        if (cmp_digits(lhs, shifted) == CmpValue::LESS) {
            --max_shift;
            break;
        }

        ++max_shift;
    }

    std::vector<unsigned int> ans;

    for (size_t shift = max_shift; shift != static_cast<size_t>(-1); --shift) {
        for (unsigned int digit = DIGIT_MAX - 1; digit != static_cast<unsigned int>(-1); --digit) {
            std::vector<unsigned int> ans_new = {digit};
            shift_digits(ans_new, shift);
            add_digits(ans_new, ans);

            std::vector<unsigned int> approx = ans_new;
            mul_digits(approx, rhs);

            if (cmp_digits(lhs, approx) != CmpValue::LESS) {
                ans = ans_new;
                break;
            }
        }
    }

    lhs = ans;
}

void Real::sqrt_digits(
    std::vector<unsigned int>& lhs
) {
    size_t max_shift = 0;
    while (true) {
        std::vector<unsigned int> shifted = {1};
        shift_digits(shifted, max_shift);

        if (cmp_digits(lhs, shifted) == CmpValue::LESS) {
            --max_shift;
            break;
        }

        ++max_shift;
    }

    std::vector<unsigned int> ans;

    for (size_t shift = max_shift; shift != static_cast<size_t>(-1); --shift) {
        for (unsigned int digit = DIGIT_MAX - 1; digit != static_cast<unsigned int>(-1); --digit) {
            std::vector<unsigned int> ans_new = {digit};
            shift_digits(ans_new, shift);
            add_digits(ans_new, ans);

            std::vector<unsigned int> approx = ans_new;
            mul_digits(approx, ans_new);

            if (cmp_digits(lhs, approx) != CmpValue::LESS) {
                ans = ans_new;
                break;
            }
        }
    }

    lhs = ans;
}

size_t Real::count_non_zero_digits(const std::vector<unsigned int>& digits) {
    assert(digits.size() != 0);
    for (size_t i = digits.size() - 1; i != static_cast<size_t>(-1); --i) {
        if (digits[i] != 0) {
            return i + 1;
        }
    }
    return 0;
}

CmpValue Real::cmp_digits(
    const std::vector<unsigned int>& lhs,
    const std::vector<unsigned int>& rhs
) {
    auto n = count_non_zero_digits(lhs);
    auto m = count_non_zero_digits(rhs);
    if (n < m) {
        return CmpValue::LESS;
    }
    if (n > m) {
        return CmpValue::GREATER;
    }

    for (size_t i = n - 1; i != static_cast<size_t>(-1); --i) {
        if (lhs[i] < rhs[i]) {
            return CmpValue::LESS;
        }
        if (lhs[i] > rhs[i]) {
            return CmpValue::GREATER;
        }
    }

    return CmpValue::EQUAL;
}

void Real::remove_leading_zeros() {
    while (!digits.empty() && digits.back() == 0) {
        digits.pop_back();
    }
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

        if (dig_cmp == CmpValue::EQUAL) {
            digits = {};
            is_positive = true;
            return *this;
        }

        if (dig_cmp == CmpValue::LESS) {
            is_positive = r.is_positive;

            Real tmp(*this);
            *this = r;

            sub_digits(digits, tmp.digits);
        } else {
            sub_digits(digits, r.digits);
        }
    }

    remove_leading_zeros();
    return *this;
}

Real& Real::operator-=(const Real& r) {
    assert(precision == r.precision);
    return operator+=(-r);
}

Real& Real::operator*=(const Real& r) {
    assert(precision == r.precision);

    is_positive ^= !r.is_positive;
    mul_digits(digits, r.digits);

    if (precision != 0 && precision - 1 < digits.size()) {
        unsigned int carry = digits[precision - 1] * 2 >= DIGIT_MAX;
        shift_digits(digits, -precision);
        add_digits(digits, {carry});
    }

    return *this;
}

Real& Real::operator/=(const Real& r) {
    assert(precision == r.precision);

    is_positive ^= !r.is_positive;
    shift_digits(digits, precision + 1);
    div_digits(digits, r.digits);

    unsigned int carry = digits[0] * 2 >= DIGIT_MAX;
    shift_digits(digits, -1);
    add_digits(digits, {carry});

    return *this;
}

Real Real::mul_sqrt(const Real& rhs) const {
    assert(precision == rhs.precision);
    assert(is_positive == rhs.is_positive);

    Real ans(*this);
    
    mul_digits(ans.digits, rhs.digits);

    shift_digits(ans.digits, 2);
    sqrt_digits(ans.digits);
    unsigned int carry = ans.digits[0] * 2 >= DIGIT_MAX;
    shift_digits(ans.digits, -1);
    add_digits(ans.digits, {carry});

    ans.remove_leading_zeros();

    return ans;
}

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

bool operator<(const Real& lhs, const Real& rhs) {
    return lhs.cmp(rhs) == CmpValue::LESS;
}

bool operator>(const Real& lhs, const Real& rhs) {
    return lhs.cmp(rhs) == CmpValue::GREATER;
}
 
bool operator<=(const Real& lhs, const Real& rhs) {
    auto cmp_val = lhs.cmp(rhs);
    return cmp_val == CmpValue::LESS || cmp_val == CmpValue::EQUAL;
}

bool operator>=(const Real& lhs, const Real& rhs) {
    auto cmp_val = lhs.cmp(rhs);
    return cmp_val == CmpValue::GREATER || cmp_val == CmpValue::EQUAL;
}

bool operator==(const Real& lhs, const Real& rhs) {
    return lhs.cmp(rhs) == CmpValue::EQUAL;
}

bool operator!=(const Real& lhs, const Real& rhs) {
    return lhs.cmp(rhs) != CmpValue::EQUAL;
}

CmpValue Real::cmp(const Real& r) const {
    assert(precision == r.precision);

    if (!is_positive && r.is_positive) {
        return CmpValue::LESS;
    }

    if (is_positive && !r.is_positive) {
        return CmpValue::GREATER;
    }

    auto cmp_dig = cmp_digits(digits, r.digits);
    return is_positive
        ? cmp_dig
        : static_cast<CmpValue>(-static_cast<int>(cmp_dig));
}

Real operator""_r(const char* num) {
    return Real(num);
}

std::string to_string(const Real& r) {
    std::stringstream ss;
    ss << r;
    return ss.str();
}
