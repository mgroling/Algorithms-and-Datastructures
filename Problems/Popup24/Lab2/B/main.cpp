// Authors: Marc Gröling

#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<Test_case> test_cases = parse_input(read_input());
    for (int i = 0; i < test_cases.size(); i++)
    {
        std::vector<std::string> result = solve_problem(test_cases[i]);
        for (int j = 0; j < result.size(); j++)
        {
            std::cout << result[j] << "\n";
        }
        if (i != test_cases.size() - 1)
        {
            std::cout << "\n";
        }
    }

    return 0;
}
