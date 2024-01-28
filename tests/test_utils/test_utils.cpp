#include "test_utils.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

const size_t Tester::TEST_MSG_WIDTH = 80;
const char* CLEAR = "\033[0m";
const char* RED = "\033[31m";
const char* GREEN = "\033[32m";

void Tester::run_test(const char* test_name, const std::function<bool()>& func) {
    std::stringstream ss;
    ss << "Test " << tests_runned + 1;
    if (test_name[0] != 0 /* if not empty */) {
        ss << " (" << test_name << ")";
    }
    ss << ' ';

    std::cout
        << std::setw(TEST_MSG_WIDTH - 7 /* length of " PASSED" */)
        << std::setfill('.')
        << std::left
        << ss.str()
        << ' ';

    if (func()) {
        std::cout << GREEN << "PASSED" << CLEAR;
        ++tests_passed;
    } else {
        std::cout << RED << "FAILED" << CLEAR;
        ++tests_failed;
    }
    std::cout << std::endl;

    ++tests_runned;
}

void Tester::print_stats() const {
    std::cout
        << '\n'
        << "STATS:\n"
        << "Tests runned: " << tests_runned << '\n'
        << "Tests passed: " << GREEN << tests_passed << CLEAR << '\n'
        << "Tests failed: " << (tests_failed == 0 ? "" : RED) << tests_failed << CLEAR << "\n\n";

    if (tests_failed != 0) {
        std::cout << RED << "!!! SOME TESTS FAILED !!!" << CLEAR;
    } else {
        std::cout << GREEN << "ALL TESTS PASSED" << CLEAR;
    }

    std::cout << std::endl;
}

bool Tester::all_passed() const {
    return tests_failed == 0;
}
