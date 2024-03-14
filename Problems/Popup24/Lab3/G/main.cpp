// Authors: Marc Gröling

#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{
        "9973 6", "1", "2", "3", "4", "9972", "9973",
    };
    std::pair<int, std::vector<int>> problem = parse_input(input);
    std::pair<int, std::vector<bool>> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
