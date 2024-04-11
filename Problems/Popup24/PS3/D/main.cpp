#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"85"};
    std::vector<int> test_cases = parse_input(input);
    std::vector<std::pair<int, int>> solution = solve_problem(test_cases);
    std::cout << format_output(solution);

    return 0;
}
