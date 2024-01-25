#include <cassert>

#include "../HW1/B/kattisio.h"
#include "../HW1/B/solution.h"

void test_1()
{
    std::vector<std::string> input{"2 2 1 1", "2 1 4 1", "20 200 3 0"};
    std::string output = "5\n"
                         "3\n"
                         "148\n";
    std::vector<Test_case> test_cases = parse_input(input);
    std::vector<int> solution = solve_problem(test_cases);
    assert(output == format_output(solution));
}

void test_2()
{
    std::vector<std::string> input{"5 5 3 2"};
    std::string output = "15\n";
    std::vector<Test_case> test_cases = parse_input(input);
    std::vector<int> solution = solve_problem(test_cases);
    assert(output == format_output(solution));
}

void test_3()
{
    std::vector<std::string> input{"8 14 6 2"};
    std::string output = "26\n";
    std::vector<Test_case> test_cases = parse_input(input);
    std::vector<int> solution = solve_problem(test_cases);
    assert(output == format_output(solution));
}

void test_4()
{
    std::vector<std::string> input{"8 14 2 4"};
    std::string output = "26\n";
    std::vector<Test_case> test_cases = parse_input(input);
    std::vector<int> solution = solve_problem(test_cases);
    assert(output == format_output(solution));
}