#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{
        "1 2 2",
        "0 0 1 1",
        "0 1",
    };
    Test_case test_case = parse_input(input);
    std::pair<int, int> solution = solve_problem(test_case);
    std::cout << solution.first << " " << solution.second << "\n";

    return 0;
}
