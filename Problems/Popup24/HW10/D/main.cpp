#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"5 6", "2 3", "3 1", "1 2", "5 1", "2 5"};
    std::vector<Test_case> problem = parse_input(read_input());
    std::vector<bool> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
