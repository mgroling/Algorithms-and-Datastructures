#include <cassert>

#include "../HW1/E/kattisio.h"
#include "../HW1/E/solution.h"

void test_1()
{
    std::vector<std::string> input{
        "how now brown <animal>", "<foo> now <color> cow", "who are you", "<a> <b> <a>", "<a> b", "c <a>"};
    std::string output = "how now brown cow\n"
                         "-\n"
                         "c b\n";
    std::vector<std::tuple<Test_case, Test_case>> test_cases = parse_input(input);
    std::vector<std::vector<std::string>> solution = solve_problem(test_cases);
    assert(output == format_output(solution));
}

void test_2()
{
    std::vector<std::string> input{"<foo> <foo> <bar> <bar>", "<foo> hello <foo> <cow>"};
    std::string output = "hello hello hello hello\n";
    std::vector<std::tuple<Test_case, Test_case>> test_cases = parse_input(input);
    std::vector<std::vector<std::string>> solution = solve_problem(test_cases);
    assert(output == format_output(solution));
}

void test_3()
{
    std::vector<std::string> input{"apple <foo> orange", "apple <bar> orange"};
    std::string output = "apple arbitrary orange\n";
    std::vector<std::tuple<Test_case, Test_case>> test_cases = parse_input(input);
    std::vector<std::vector<std::string>> solution = solve_problem(test_cases);
    assert(output == format_output(solution));
}

void test_4()
{
    std::vector<std::string> input{"apple <foo> orange", "banana <bar> grape"};
    std::string output = "-\n";
    std::vector<std::tuple<Test_case, Test_case>> test_cases = parse_input(input);
    std::vector<std::vector<std::string>> solution = solve_problem(test_cases);
    assert(output == format_output(solution));
}

void test_5()
{
    std::vector<std::string> input{"<a> <a> <a>", "<foo> <foo> <bar>"};
    std::string output = "arbitrary arbitrary arbitrary\n";
    std::vector<std::tuple<Test_case, Test_case>> test_cases = parse_input(input);
    std::vector<std::vector<std::string>> solution = solve_problem(test_cases);
    assert(output == format_output(solution));
}

void test_6()
{
    std::vector<std::string> input{"<foo> <bar> is a <adj> <adj> but <hey>",
                                   "<bar> <foo> <bar> <foo> nice <adj> <hey> <adj>"};
    std::string output = "is a is a nice nice but nice\n";
    std::vector<std::tuple<Test_case, Test_case>> test_cases = parse_input(input);
    std::vector<std::vector<std::string>> solution = solve_problem(test_cases);
    assert(output == format_output(solution));
}

void test_7()
{
    std::vector<std::string> input{"<foo> <bar> is a <adj> <adj> but <foo>",
                                   "<bar> <foo> <bar> <foo> nice <adj> <hey> <adj>"};
    std::string output = "-\n";
    std::vector<std::tuple<Test_case, Test_case>> test_cases = parse_input(input);
    std::vector<std::vector<std::string>> solution = solve_problem(test_cases);
    assert(output == format_output(solution));
}