#include "kattisio.h"
#include "solution.h"

#include <chrono>

struct Timer
{
    std::chrono::_V2::system_clock::time_point start;

    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        std::cout << "Program took "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() -
                                                                           start)
                         .count()
                  << "ms to execute\n";
    }
};

int main()
{
    // std::vector<std::string> input{
    //     "3 4",
    //     "2 3 2",
    //     "1 1 3 2",
    // };
    std::vector<std::string> input;
    std::string temp = "";
    for (int i = 0; i < 100; i++)
    {
        temp += "100";
        if (i != 99)
        {
            temp += " ";
        }
    }
    input.push_back("100 100");
    input.push_back(temp);
    input.push_back(temp);

    Timer timer;
    std::pair<std::vector<int>, std::vector<int>> problem = parse_input(input);
    bool solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
