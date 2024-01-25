#include <cassert>

#include "../HW1/F/kattisio.h"
#include "../HW1/F/solution.h"

void test_1()
{
    std::vector<int> input{900, 500, 498, 4};
    int output = 1002;
    int solution = solve_problem(input);
    assert(solution == output);
}

void test_2()
{
    std::vector<int> input{1};
    int output = 1;
    int solution = solve_problem(input);
    assert(solution == output);
}