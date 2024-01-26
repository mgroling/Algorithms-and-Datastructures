#include <cassert>
#include <cmath>

#include "../HW1/D/kattisio.h"
#include "../HW1/D/solution.h"

void test_1()
{
    std::vector<std::string> input{"buy 1 15", "split 3", "sell 1 5", "die 4"};
    long double output = 8.0L;
    std::vector<Transaction> transactions = parse_input(input);
    long double solution = solve_problem(transactions);
    assert(std::abs(output - solution) < 0.01);
}

void test_2()
{
    std::vector<std::string> input{"buy 10 10", "buy 30 5", "sell 31 8", "split 2", "merge 8", "die 42"};
    long double output = 73.8L;
    std::vector<Transaction> transactions = parse_input(input);
    long double solution = solve_problem(transactions);
    assert(std::abs(output - solution) < 0.01);
}

void test_3()
{
    std::vector<std::string> input{"buy 1000 1000", "buy 999 999", "split 497", "merge 727", "die 1000"};
    long double output = 1366000L;
    std::vector<Transaction> transactions = parse_input(input);
    long double solution = solve_problem(transactions);
    assert(std::abs(output - solution) < 0.01);
}

void test_4()
{
    std::vector<std::string> input;
    input.emplace_back("buy 92685293 1225184279");
    for (int i = 0; i < 10000; i++)
    {
        input.emplace_back("split 497");
        input.emplace_back("merge 497");
        input.emplace_back("buy 72931234 1225184279");
        input.emplace_back("sell 72931234 1");
    }
    input.emplace_back("die 1425623124");

    long double output = 126560977032293356.5L;
    std::vector<Transaction> transactions = parse_input(input);
    long double solution = solve_problem(transactions);
    assert(std::abs(output - solution) < 0.01);
}