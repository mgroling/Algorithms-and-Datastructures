// Authors: Marc Gröling

#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::vector<int>> problem = parse_input(read_input());
    std::vector<std::vector<std::pair<double, double>>> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
