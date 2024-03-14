// Authors: Marc Gröling

#include "kattisio.h"
#include "solution.h"

int main()
{
    std::pair<int, std::vector<int>> problem = parse_input(read_input());
    std::pair<int, std::vector<bool>> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
