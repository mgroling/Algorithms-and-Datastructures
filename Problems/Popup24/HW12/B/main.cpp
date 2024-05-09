#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"6", "1 2 3 4 5 6", "359997 359998 359999 0 1 2"};
    std::pair<std::vector<int>, std::vector<int>> problem = parse_input(input);
    bool solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
