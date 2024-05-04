// Authors: Marc Gröling

#include "../geometry.h"

#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{
        "5", "0 1", "0 2", "0 3", "0 4", "0 5",
    };
    std::vector<std::vector<Point<double>>> problem = parse_input(input);
    std::vector<std::vector<double>> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
