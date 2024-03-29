// Authors: Marc Gröling

#include "../modular_arithmetic.h"
#include "kattisio.h"

#include <vector>

std::vector<long long> solve_problem(const Test_case &input)
{
    std::vector<long long> output;

    for (const std::pair<long long, long long> &query : input.queries)
    {
        output.push_back(
            compute_linear_recurrence_modulo(input.coefficients, input.initial_values, query.first, query.second));
    }

    return output;
}