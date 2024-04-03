#include "kattisio.h"
#include "solution.h"

#include <random>

std::string generateRandomDigits(int n)
{
    std::random_device rd;  // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator

    std::uniform_int_distribution<> distrib(0, 9); // define the range

    std::string result;
    for (int i = 0; i < n; ++i)
    {
        result += std::to_string(distrib(gen)); // generate a random digit and append it to the string
    }
    return result;
}

int main()
{
    // std::vector<std::string> input{"67.9"};
    // std::vector<std::string> problem = parse_input(input);
    // std::vector<std::string> solution = solve_problem(problem);
    // std::cout << format_output(solution);

    std::string string = "37993";
    std::cout << solve_test_case(string) << "\n";
    std::cout << solve_test_case_naive(string) << "\n";

    // for (int i = 0; i < 5; i++)
    // {
    //     std::string string = generateRandomDigits(5);
    //     if (solve_test_case(string) != solve_test_case_naive(string))
    //     {
    //         std::cout << string << "\n";
    //     }
    // }

    return 0;
}
