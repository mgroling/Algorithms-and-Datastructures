#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> test_cases = parse_input(read_input());
    std::vector<int> solution = solve_problem(test_cases);
    std::cout << format_output(solution);

    return 0;
}
