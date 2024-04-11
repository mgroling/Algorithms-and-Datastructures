#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"7",
                                   "als mollen mollen mollen mollen mollen mollen",
                                   "4",
                                   "als when incorrect",
                                   "mollen moles correct",
                                   "mollen destroy correct",
                                   "mollen mills incorrect"};
    Test_case test_case = parse_input(input);
    std::vector<std::string> solution = solve_problem(test_case);
    std::cout << format_output(solution);

    return 0;
}
