#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<Test_case> test_cases = parse_input(read_input());
    std::string solution = solve_problem(test_cases);
    std::cout << solution;

    return 0;
}
