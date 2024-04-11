#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"ABABABcABABAbAbab", "0 2", "1 6", "0 7"};
    Test_case test_case = parse_input(read_input());
    std::vector<int> solution = solve_problem(test_case);
    std::cout << format_output(solution);

    return 0;
}
