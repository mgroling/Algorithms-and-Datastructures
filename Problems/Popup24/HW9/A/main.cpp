#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> test_cases = parse_input(read_input());
    std::vector<int> solution = solve_problem(test_cases);
    std::cout << format_output(solution);

    // 0  1  2  3  4
    // 5  6  7  8  9
    // 10 11 12 13 14
    // 15 16 17 18 19
    // 20 21 22 23 24

    // 1 1 1 1 1
    // 0 1 1 1 1
    // 0 0   1 1
    // 0 0 0 0 1
    // 0 0 0 0 0
    std::string goal = "111110111100 110000100000";
    // 1 1 1   1
    // 0 1 1 1 1
    // 0 0 1 1 1
    // 0 0 0 0 1
    // 0 0 0 0 0
    std::string pos1 = "111 101111001110000100000";
    // 1 1 1 1 1
    // 0 1 1 1 1
    // 0 0 1 1
    // 0 0 0 0 1
    // 0 0 0 0 0
    std::string pos2 = "11111011110011 0000100000";
    // 1 1 1 1 1
    // 0 1 1 1 1
    // 0 0 1 1 0
    // 0 0   0 1
    // 0 0 0 0 0
    std::string pos3 = "11111011110011000 0100000";
    // 1 1 1 1 1
    // 0   1 1 1
    // 0 0 1 1 0
    // 0 0 1 0 1
    // 0 0 0 0 0
    std::string pos4 = "111110 111001100010100000";
    // 1 1 1 1 1
    // 0 0 1 1 1
    // 0 0 1 1 0
    //   0 1 0 1
    // 0 0 0 0 0
    std::string pos5 = "111110011100110 010100000";

    // std::cout << solve_test_case(pos1) << '\n';

    return 0;
}
