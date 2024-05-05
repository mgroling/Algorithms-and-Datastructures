#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"3 3 3", "4 4 5"};
    std::vector<std::tuple<int, int, int>> problem = parse_input(read_input());
    double solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
