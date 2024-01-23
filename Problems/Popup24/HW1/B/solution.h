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

First notice, that it is always better to spend crowns of higher value first (we first want to spend all coins of 10
crowns, then of 5, and then of 1). Also notice, that we can just buy all of them at once and ignore that we get change.
For each test case, we can compute the value of the cokes that we want to buy (i.e. we want 12 cokes, so they cost 96
Swedish crowns). As such for the example of 96 crowns, we could pay it with 10 10-crown pieces. However, we might not
have 10 10-crown pieces, but we use all that we have. Let's say we only have 3. As such, 7 are missing. For these 7, we
can use 7 * 2 = 14 5-crown coins instead (however notice that we might need one less 5-crown piece in some cases). But
again, we might not have that many 5-crown coins. This goes on until we have the values for all 3 coin types. Then we
can just sum them up and get the result.

*/

#include "kattisio.h"

#include <cmath>
#include <vector>

int solve_test_case(const Test_case &test_case)
{
    int value_cokes = test_case.num_cokes_to_buy * 8;
    int coins_10_required = std::ceil(value_cokes / 10.0);

    int coins_10_unavailable = std::max(coins_10_required - test_case.num_10_coins, 0);
    int coins_10_used = coins_10_required - coins_10_unavailable;
    int coins_5_required = coins_10_unavailable * 2 - (value_cokes % 10 <= 5 && value_cokes % 10 != 0);
    int coins_5_unavailable = std::max(coins_5_required - test_case.num_5_coins, 0);
    int coins_5_used = coins_5_required - coins_5_unavailable;
    int coins_1_used = std::max(value_cokes - coins_10_used * 10 - coins_5_used * 5, 0);

    return coins_10_used + coins_5_used + coins_1_used;
}

std::vector<int> solve_problem(const std::vector<Test_case> &test_cases)
{
    std::vector<int> output;

    for (const Test_case &test_case : test_cases)
    {
        output.emplace_back(solve_test_case(test_case));
    }

    return output;
}