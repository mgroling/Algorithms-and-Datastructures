#include "kattisio.h"
#include "solution.h"

#include <algorithm>

int main()
{
    std::vector<std::string> input{"6"};
    std::vector<long long> problem = parse_input(input);
    std::vector<long long> solution = solve_problem(problem);
    std::vector<long long> solution_naive = solve_problem_naive(problem);
    std::cout << format_output(solution);
    std::cout << format_output(solution_naive);

    // std::vector<long long> factors = find_non_trivial_factors(6LL);
    // std::sort(factors.begin(), factors.end());
    // for (const long long &factor : factors)
    // {
    //     std::cout << factor << "\n";
    // }

    return 0;
}
