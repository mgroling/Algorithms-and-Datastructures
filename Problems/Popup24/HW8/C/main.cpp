#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::pair<int, std::string>> problem = parse_input(read_input());
    std::vector<long long> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}