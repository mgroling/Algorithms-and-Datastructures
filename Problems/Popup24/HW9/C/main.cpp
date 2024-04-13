#include "kattisio.h"
#include "solution.h"

int main()
{
    std::pair<std::vector<uint8_t>, std::vector<std::pair<uint16_t, uint16_t>>> problem = parse_input(read_input());
    int8_t solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
