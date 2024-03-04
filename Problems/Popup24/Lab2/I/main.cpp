// Authors: Marc Gröling

#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"2 1", "0 1"};
    std::vector<Test_case> test_cases = parse_input(input);
    for (int i = 0; i < test_cases.size(); i++)
    {
        std::string result = solve_problem(test_cases[i]);
        std::cout << result << "\n";
    }

    return 0;
}