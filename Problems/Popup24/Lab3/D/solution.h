// Authors: Marc Gröling

#include "../modular_arithmetic.h"
#include "kattisio.h"

#include <vector>

std::vector<std::pair<bool, unsigned long long>> solve_problem(const std::vector<Test_case> &input)
{
    std::vector<std::pair<bool, unsigned long long>> output;

    for (const Test_case &test_case : input)
    {
        // could also put corresponding methods in a dictionary, which might be more readable, but I prefer this I think
        if (test_case.operator_ == "+")
        {
            output.emplace_back(true, modulo_add(test_case.num1, test_case.num2, test_case.modulus));
        }
        else if (test_case.operator_ == "-")
        {
            output.emplace_back(true, modulo_subtract(test_case.num1, test_case.num2, test_case.modulus));
        }
        else if (test_case.operator_ == "*")
        {
            output.emplace_back(true, modulo_multiply(test_case.num1, test_case.num2, test_case.modulus));
        }
        else if (test_case.operator_ == "/")
        {
            output.emplace_back(modulo_divide(test_case.num1, test_case.num2, test_case.modulus));
        }
    }

    return output;
}