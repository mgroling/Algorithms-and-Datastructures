// Authors: Marc Gröling

#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"Suffixes are jolly fun, eh old chap?", "1 0"};
    std::vector<Test_case> problem = parse_input(input);
    std::vector<std::vector<int>> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
