#include <cstdlib>
#include <functional>

class Tester {
    public:
        void run_test(const char* test_name, const std::function<bool()>& func);

        void print_stats() const;

        bool all_passed() const;

    private:
        size_t tests_runned = 0;
        size_t tests_passed = 0;
        size_t tests_failed = 0;

        static const size_t TEST_MSG_WIDTH;
};

#define TESTING_BEGIN \
   int main() { \
        Tester tester;

#define TESTING_END \
        tester.print_stats(); \
        return tester.all_passed() \
            ? EXIT_SUCCESS \
            : EXIT_FAILURE; \
    }

#define TEST(test_name) \
    tester.run_test( \
        #test_name, \
        []() {

#define ENDTEST \
            return true; \
        } \
    );

#define ASSERT(x) if (!(x)) { return false; } else {}

#define ASSERT_EQ(x, y) ASSERT((x) == (y))
