#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"3", "1 2", "1 100", "1 1"};
    std::vector<std::vector<int>> problem = parse_input(read_input());
    std::vector<int> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
