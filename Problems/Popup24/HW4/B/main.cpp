#include "kattisio.h"
#include "solution.h"

int main()
{
    std::tuple<long long, long long, int> parameters = read_input();
    std::tuple<long long, long long> solution =
        solve_problem(std::get<0>(parameters), std::get<1>(parameters), std::get<2>(parameters));
    std::cout << std::get<0>(solution) << "\n" << std::get<1>(solution) << "\n";

    return 0;
}
