#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"8", "cabcabca"};
    std::string problem = parse_input(input);
    int solution = solve_problem(problem);
    std::cout << solution << '\n';

    return 0;
}
