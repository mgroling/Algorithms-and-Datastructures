#include "kattisio.h"
#include "solution_slow.h"

int main()
{
    std::tuple<long long, long long, int> parameters{1L, 9999L, 9};
    std::tuple<long long, long long> solution =
        solve_problem(std::get<0>(parameters), std::get<1>(parameters), std::get<2>(parameters));
    std::cout << std::get<0>(solution) << "\n" << std::get<1>(solution) << "\n";

    return 0;
}
