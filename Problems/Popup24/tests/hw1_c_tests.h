#include <cassert>

#include "../HW1/C/kattisio.h"
#include "../HW1/C/solution.h"

void test_1()
{
    std::string output = "1\n";
    std::vector<int> input{1};
    std::vector<std::vector<int>> solution = solve_problem(input);
    assert(output == format_output(solution));
}

void test_2()
{
    std::string output = "2 1\n";
    std::vector<int> input{2};
    std::vector<std::vector<int>> solution = solve_problem(input);
    assert(output == format_output(solution));
}

void test_3()
{
    std::string output = "3 1 2\n";
    std::vector<int> input{3};
    std::vector<std::vector<int>> solution = solve_problem(input);
    assert(output == format_output(solution));
}

void test_4()
{
    std::string output = "2 1 4 3\n";
    std::vector<int> input{4};
    std::vector<std::vector<int>> solution = solve_problem(input);
    assert(output == format_output(solution));
}

void test_5()
{
    std::string output = "3 1 4 5 2\n";
    std::vector<int> input{5};
    std::vector<std::vector<int>> solution = solve_problem(input);
    assert(output == format_output(solution));
}