#include "kattisio.h"
#include "solution.h"

int main()
{
    std::pair<std::vector<Point<long double>>, long double> problem = parse_input(read_input());
    std::pair<int, std::vector<long double>> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
