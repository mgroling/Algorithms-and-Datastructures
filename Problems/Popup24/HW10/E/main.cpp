#include "kattisio.h"
#include "solution.h"

int main()
{
    long long problem = parse_input(read_input());
    std::pair<std::string, std::string> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
