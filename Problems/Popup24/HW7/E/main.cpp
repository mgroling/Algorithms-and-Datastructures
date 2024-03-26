#include "kattisio.h"
#include "solution.h"

int main()
{
    std::string problem = parse_input(read_input());
    int solution = solve_problem(problem);
    std::cout << solution << '\n';

    return 0;
}
