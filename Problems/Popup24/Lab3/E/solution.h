// Authors: Marc Gröling

#include "../modular_arithmetic.h"
#include "kattisio.h"

#include <vector>

std::vector<std::pair<unsigned long long, unsigned long long>> solve_problem(const std::vector<Test_case> &input)
{
    std::vector<std::pair<unsigned long long, unsigned long long>> output;

    for (const Test_case &test_case : input)
    {
        output.emplace_back(chinese_remainder_coprime(test_case.a, test_case.b, test_case.n, test_case.m));
    }

    return output;
}