#pragma once

#include <vector>
#include <iostream>
#include <string>

class Real;

std::ostream& operator<<(std::ostream&, const Real&);

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

        // Condition  | Return Value
        // -------------------------
        // *this < r  |      -1
        // *this == r |       0
        // *this > r  |      +1
        int cmp(const Real& r) const;

    private:
        static void add_digits(
            std::vector<unsigned int>& lhs,
            const std::vector<unsigned int>& rhs
        );

        static void sub_digits(
            std::vector<unsigned int>& lhs,
            const std::vector<unsigned int>& rhs
        );

        // Return value works like in cmp function
        static int cmp_digits(
            const std::vector<unsigned int>& lhs,
            const std::vector<unsigned int>& rhs
        );

        static size_t count_non_zero_digits(const std::vector<unsigned int>& digits);

        static const unsigned int digit_size;

        bool is_positive;
        std::vector<unsigned int> digits;
        size_t precision; // number of digits after dot

    friend std::ostream& operator<<(std::ostream&, const Real&);
};

Real operator+(const Real&, const Real&);
Real operator-(const Real&, const Real&);
Real operator*(const Real&, const Real&);
Real operator/(const Real&, const Real&);
