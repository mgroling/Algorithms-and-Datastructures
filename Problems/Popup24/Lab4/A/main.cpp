// Authors: Marc Gröling

#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"abcdefgabcdefg", "2", "0 7", "7 14"};
    std::pair<std::string, std::vector<std::pair<int, int>>> problem = parse_input(input);
    std::vector<uint64_t> solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
