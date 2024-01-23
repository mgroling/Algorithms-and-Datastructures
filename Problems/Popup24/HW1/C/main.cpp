#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<int> test_cases = read_input();
    std::vector<std::vector<int>> solution = solve_problem(test_cases);
    std::cout << format_output(solution);

    return 0;
}
