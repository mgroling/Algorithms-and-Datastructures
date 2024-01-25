/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

I often buy Coca-Cola from the vending machine at work. Usually I buy several cokes at once, since my working mates also
likes coke. A coke in the vending machine costs 8 Swedish crowns, and the machine accept crowns with the values 1, 5
and 10. As soon as I press the coke button (after having inserted sufficient amount of money), I receive a coke followed
by the exchange (if any). The exchange is always given in as few coins as possible (this is uniquely determined by the
coin set used). This procedure is repeated until I’ve bought all the cokes I want. Note that I can pick up the coin
exchange and use those coins when buying further cokes.

Now, what is the least number of coins I must insert, given the number of cokes I want to buy and the number of coins I
have of each value? Please help me solve this problem while I create some harder problems for you. You may assume that
the machine won’t run out of coins and that I always have enough coins to buy all the cokes I want.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line in the input contains the number of test cases (at most 100). Each case is then given on a line by
itself. A test case consists of four integers: C (the number of cokes I want to buy), n_1, n_5, n_10 (the number of
coins of value 1, 5 and 10, respectively). The input limits are 1 <= C <= 150, 0 <= n_1 <= 500, 0 <= n_5 <= 100 and 0 <=
n_10 <= 50.

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each test case, output a line containing a single integer: the minimum number of coins needed to insert into the
vending machine.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
3
2 2 1 1
2 1 4 1
20 200 3 0

Sample Output 1:
5
3
148

----------------------------------------------------- SOLUTION -----------------------------------------------------



*/

#include "kattisio.h"

#include <cassert>
#include <cmath>
#include <vector>

int solve_test_case_only_1_5_coins(Test_case &test_case)
{
    assert(test_case.num_10_coins == 0);

    if (test_case.num_5_coins > 2 * test_case.num_cokes_to_buy)
    {
        return 2 * test_case.num_cokes_to_buy;
    }
    int num_5_5_pairs = std::max(test_case.num_5_coins - test_case.num_cokes_to_buy, 0);
    int num_5_3_pairs = test_case.num_5_coins - 2 * num_5_5_pairs;
    int num_8_coins = test_case.num_cokes_to_buy - num_5_5_pairs - num_5_3_pairs;

    return num_5_5_pairs * 2 + num_5_3_pairs * 4 + num_8_coins * 8;
}

int solve_test_case(Test_case &test_case)
{
    int coins_10_required = test_case.num_cokes_to_buy;

    if (coins_10_required <= test_case.num_10_coins)
    {
        return coins_10_required;
    }

    int coins_10_unavailable = std::max(coins_10_required - test_case.num_10_coins, 0);
    int coins_5_required = coins_10_unavailable;
    int coins_5_unavailable = coins_5_required - test_case.num_5_coins;

    int num_coins_used = 0;
    // TODO: could do this without a loop, but it works and I don't want to spend time on it right now, so...
    while (test_case.num_10_coins > 0)
    {
        // there is still a need for 5-crown coins and we have sufficient resources
        // => trade 1 10-crown coin + 3 1-crown coins for a coke and a 5-crown coin
        if (coins_5_unavailable > 0 && test_case.num_1_coins >= 3)
        {
            test_case.num_10_coins--;
            test_case.num_5_coins++;
            coins_5_unavailable--;
            test_case.num_1_coins -= 3;
            num_coins_used += 4;
        }
        else
        {
            test_case.num_10_coins--;
            test_case.num_1_coins += 2;
            num_coins_used++;
        }
        test_case.num_cokes_to_buy--;
    }

    return num_coins_used + solve_test_case_only_1_5_coins(test_case);
}

std::vector<int> solve_problem(std::vector<Test_case> &test_cases)
{
    std::vector<int> output;

    for (Test_case &test_case : test_cases)
    {
        output.emplace_back(solve_test_case(test_case));
    }

    return output;
}