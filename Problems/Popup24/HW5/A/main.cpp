#include "kattisio.h"
#include "solution.h"

int main()
{
    Test_case test_case = parse_input(read_input());
    int solution = solve_problem(test_case);
    std::cout << solution << "\n";

    return 0;
}
