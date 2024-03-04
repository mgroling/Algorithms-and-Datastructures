#include "kattisio.h"
#include "solution.h"

#include <iomanip>
#include <limits>

int main()
{
    std::vector<std::string> input{
        "2",
        "100 100",
        "50 50",
    };
    std::vector<std::vector<int>> test_case = parse_input(read_input());
    long double solution = solve_problem(test_case);
    std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10) << solution << "\n";
    return 0;
}
