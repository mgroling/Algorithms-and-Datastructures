// Authors: Marc Gröling

#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"1 1 1 1 2 1 2 1"};
    std::vector<std::vector<int>> problem = parse_input(input);
    std::vector<double> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
