#include "kattisio.h"
#include "solution.h"

int main()
{
    Test_case problem = parse_input(read_input());
    int solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
