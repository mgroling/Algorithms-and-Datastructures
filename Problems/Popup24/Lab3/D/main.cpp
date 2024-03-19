// Authors: Marc Gröling

#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<Test_case> problem = parse_input(read_input());
    std::vector<std::pair<bool, long long>> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
