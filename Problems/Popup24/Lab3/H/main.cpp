// Authors: Marc Gröling

#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{
        "2", "0 1 1", "0 1", "6", "1 100000", "2 100000", "3 100000", "4 100000", "5 100000", "6 100000",
    };
    Test_case problem = parse_input(read_input());
    std::vector<long long> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
