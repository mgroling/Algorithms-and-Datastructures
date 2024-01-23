#include <cassert>

#include "../HW1/B/kattisio.h"
#include "../HW1/B/solution.h"

void test_1()
{
    std::vector<std::string> input{"2 2 1 1", "2 1 4 1", "20 200 3 0"};
    std::string output = "3\n"
                         "3\n"
                         "148\n";
    std::vector<int> solution = solve_problem(parse_input(input));
    assert(output == format_output(solution));
}
