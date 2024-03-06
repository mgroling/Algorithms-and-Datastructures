#include "kattisio.h"
#include "solution.h"

int main()
{
    std::pair<int, std::vector<std::pair<int, int>>> test_case = parse_input(read_input());
    std::string solution = solve_problem(test_case);
    std::cout << solution << "\n";

    return 0;
}
