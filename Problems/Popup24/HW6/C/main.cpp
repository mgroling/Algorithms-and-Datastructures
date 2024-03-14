#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{
        "7 7", "10 10 1 10 10 10 10", "0 5 1", "0 6 5", "6 2 5", "2 5 5", "5 4 1", "2 1 50", "4 3 50", "1", "50 0 3"};
    Test_case test_case = parse_input(input);
    std::vector<int> solution = solve_problem(test_case);
    std::cout << format_output(solution);

    return 0;
}
