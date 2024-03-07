#include "kattisio.h"
#include "solution.h"

int main()
{
    std::pair<std::vector<int>, std::vector<int>> problem = parse_input(read_input());
    bool solution = solve_problem(problem.first, problem.second);
    std::cout << format_output(solution);

    return 0;
}
