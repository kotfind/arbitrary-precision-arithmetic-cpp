#pragma once

#include <vector>
#include <iostream>
#include <string>

class Real;

std::ostream& operator<<(std::ostream&, const Real&);

enum class CmpValue {
    LESS    = -1,
    EQUAL   =  0,
    GREATER = +1,
};

class Real {
    public:
        Real(bool is_positive, const std::vector<unsigned int>& digits, size_t precision);
        explicit Real(const std::string& number);
        Real(const Real& r);

        Real& operator=(const Real&);

        Real& operator+=(const Real&);
        Real& operator-=(const Real&);
        Real& operator*=(const Real&);
        Real& operator/=(const Real&);

        Real operator-() const;
        Real operator+() const;

        CmpValue cmp(const Real& r) const;

    private:
        static void add_digits(
            std::vector<unsigned int>& lhs,
            const std::vector<unsigned int>& rhs
        );

        static void sub_digits(
            std::vector<unsigned int>& lhs,
            const std::vector<unsigned int>& rhs
        );

        static void shift_digits(
            std::vector<unsigned int>& lhs,
            int shift
        );

        static void mul_digits(
            std::vector<unsigned int>& lhs,
            const std::vector<unsigned int>& rhs
        );

        static void div_digits(
            std::vector<unsigned int>& lhs,
            const std::vector<unsigned int>& rhs
        );

        static CmpValue cmp_digits(
            const std::vector<unsigned int>& lhs,
            const std::vector<unsigned int>& rhs
        );

        static size_t count_non_zero_digits(const std::vector<unsigned int>& digits);

        void remove_leading_zeros();

        static const unsigned int DIGIT_MAX;

        bool is_positive;
        std::vector<unsigned int> digits;
        size_t precision; // number of digits after dot

    friend std::ostream& operator<<(std::ostream&, const Real&);
};

Real operator+(const Real&, const Real&);
Real operator-(const Real&, const Real&);
Real operator*(const Real&, const Real&);
Real operator/(const Real&, const Real&);

bool operator<(const Real&, const Real&);
bool operator>(const Real&, const Real&);
bool operator<=(const Real&, const Real&);
bool operator>=(const Real&, const Real&);
bool operator==(const Real&, const Real&);
bool operator!=(const Real&, const Real&);
