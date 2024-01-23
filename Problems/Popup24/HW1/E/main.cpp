#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::tuple<Test_case, Test_case>> test_cases = parse_input(read_input());
    std::vector<std::vector<std::string>> solution = solve_problem(test_cases);
    std::cout << format_output(solution);

    return 0;
}
