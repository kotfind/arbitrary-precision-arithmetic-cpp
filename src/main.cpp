#include "Real.hpp"

#include <iostream>

int main() {
    std::cout << std::boolalpha << (Real("-2.000") < Real("1.000")) << '\n';
}
