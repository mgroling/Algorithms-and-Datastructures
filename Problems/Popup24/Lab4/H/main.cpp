// Authors: Marc Gröling

#include "../geometry.h"

#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::vector<Point<int>>> problem = parse_input(read_input());
    std::vector<std::vector<Point<int>>> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
