#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"50", "5", "110 10", "80 10", "80 0", "110 0", "130 40"};
    std::pair<std::vector<Point<long double>>, long double> problem = parse_input(input);
    std::pair<int, std::vector<long double>> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
