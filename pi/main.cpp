#include "Real.hpp"

#include <ios>
#include <iostream>
#include <ctime>
#include <limits>

Real calculate_pi(size_t precision);

Real calculate_pi(size_t p) {
    auto C = Real("426880", p) * Real("10005", p).mul_sqrt(Real(1, p));
    auto S = Real("0", p);
    auto Mq = Real("1", p);
    auto Lq = Real("13591409", p);
    auto Xq = Real("1", p);

    for (size_t q = 0; q < p / 14 + 1; ++q) {
        S += Mq * Lq / Xq;
        Mq *= Real(8 * (6*q + 1) * (6*q + 3) * (6*q + 5), p);
        Mq /= Real((q + 1)*(q + 1)*(q + 1), p);
        Lq += Real("545140134", p);
        Xq *= Real("-262537412640768000", p);
    }

    return C / S;
}

template<typename T>
T read(const char* prompt) {
    T value;

    for(;;) {
        std::cout << prompt;
        if (std::cin >> value) {
            break;
        } else {
            std::cout << "error: could not parse" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    
    return value;
}

int main() {
    auto precision = read<size_t>("Enter precision: ");

    auto start_time = clock();
    auto pi = calculate_pi(precision);
    auto finish_time = clock();

    auto duration = static_cast<double>(finish_time - start_time) / CLOCKS_PER_SEC;

    std::cout
        << "Pi: " << pi << '\n'
        << "CPU time: " << duration << '\n'
        << std::flush;
}

