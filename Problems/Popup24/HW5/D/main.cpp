#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<Ballot> ballots = parse_input(read_input());
    std::vector<bool> solution = solve_problem(ballots);
    std::cout << format_output(solution);

    return 0;
}
