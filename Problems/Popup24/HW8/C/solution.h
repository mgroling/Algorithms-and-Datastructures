/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include <string>
#include <vector>

long long solve_test_case(std::pair<int, std::string> test_case)
{
    // substring has length 1 => only 1 possible binary string
    if (test_case.second.size() == 1)
    {
        return 1;
    }

    // row is n, col is the equation
    std::vector<std::vector<long long>> dp_table(test_case.first, std::vector<long long>(test_case.second.size(), 0));
    // example: b = 01011
    // 0: a(n) := # bit-strings of size n that end with 0 and don't contain b
    // 1: b(n) := # bit-strings of size n that end with 1 and don't contain b
    // 2: c(n) := # bit-strings of size n that end with 11 and don't contain b
    // 3: d(n) := # bit-strings of size n that end with 001 and don't contain b
    // 4: e(n) := # bit-strings of size n that end with 1101 and don't contain b
    // a(n) = a(n-1) + b(n-1)
    // b(n) = a(n-1) + c(n-1) + d(n-1) + e(n-1)
    // c(n) = b(n-2)
    // d(n) = a(n-2)
    // e(n) = b(n-3)

    std::vector<std::pair<bool, int>> recursion_formulas;
}

std::vector<long long> solve_problem(const std::vector<std::pair<int, std::string>> &problem)
{
    std::vector<long long> output;

    for (const std::pair<int, std::string> &elem : problem)
    {
        output.emplace_back(solve_test_case(elem));
    }

    return output;
}