/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

Kattis’ grumpy old aunt Mittens in Taxmania has recently died at a tender age of 109 cat years. Among her many papers
are her stock records. As it turns out, Mittens traded a lot in the stock of her namesake mitten-producing company
Mittens Conglomerated.

In Taxmania dead cats are prohibited from owning stock, so when Mittens died, all her shares (units) of stock in Mittens
Conglomerated were sold, with 30% of the capital gains paid as taxes. Your task is to compute how much money the final
sale of Mittens’ shares yields, after paying taxes on the profits. There are no tax effects from selling at a loss.

Mittens stock records indicate the history of her purchases and sales of shares, and at what costs they were made. In
addition, they indicate when the company performed splits and merges of its stock. When the company splits its stock,
every share is replaced by x new shares, and the value divided evenly between them. When the company merges its stock,
every x shares are replaced by a single stock. If Mittens can not merge all her shares (due to her number of shares not
being divisible by x), she is forced to sell any remainder stock (at a price equal to the current average cost of her
shares).

For example, consider the following sequence of events (corresponding to Sample Input 2):

    1. Mittens buys 10 shares for 10 crowns per share.

    2. Mittens buys 30 shares for crowns per share. The average cost of her shares is now (10 * 10 + 30 * 5) / (10 + 30)
= 6.25 crowns.

    3. Mittens sells 31 shares for 8 crowns per share. The profit is 8 - 6.25 crowns per share (which is subject to
capital gains tax but that is irrelevant). The sale does not change the average cost of Mittens’ shares.

    4. The company performs a split with x = 2. Mittens’ shares split into 2 * 9 = 18 shares, of average cost 6.25/2
= 3.125.

    5. The company performs a merge with x = 8. Mittens merges 16 of her 18 shares into 2 new shares of average cost
8 * 3.125 = 25. The last two remaining old shares can not be merged and Mittens is forced to sell them.

    6. Mittens dies and her 2 shares are sold for 42 crowns per share. The profit is 42 - 25 = 17 crowns per share,
which is subject to the 30% tax. The total amount obtained from the final sale after taxes is thus 2 * (42 - 17 * 0.3)
= 73.8 crowns.

----------------------------------------------------- INPUT -----------------------------------------------------

The input contains a sequence of at most 10000 events in chronological order. Each event is in one of the following
forms:

    “buy x y”: Mittens bought x shares of stock at y crowns per share.

    “sell x y”: Mittens sold x shares of stock at y crowns per share (and used the money for purposes unknown). The
value of x is no greater than the number of shares owned before the event.

    “split x”: The stock split with x new shares for each share.

    “merge x”: The stock merged with one new share for every x shares.

    “die y”: The remaining shares were sold off at the death of Mittens for y crowns per share. This event happens
exactly once and is guaranteed to be the last event in the input.

In all events, x and y are integers satisfying 1 <= x, y <= 1000. You may assume that at any point in time in the event
history, the total number of shares of stock owned by Mittens was at most 10^6.

----------------------------------------------------- OUTPUT -----------------------------------------------------

Output a single line containing the number of crowns obtained (after paying taxes) in the final sale of Mittens’ stock
after her death. The answer should be accurate to within an absolute error of at most 0.01.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
buy 1 15
split 3
sell 1 5
die 4

Sample Output 1:
8.00000000


Sample Input 2:
buy 10 10
buy 30 5
sell 31 8
split 2
merge 8
die 42

Sample Output 2:
73.8

----------------------------------------------------- SOLUTION -----------------------------------------------------

All the operations that Mittens can do are rather easy to translate into arithmetic operation. The only problem is that
the result should be accurate up to an absolute error of 0.01. Using long datatypes (long long and long double) was
sufficient.

I also added a small thing in the buying procedure, when computing the weighted average of the two stock shares, we can
compute the greatest common divisor between the number of stock shares bought and owned. This can then be used to keep
the result smaller, which should help with precision issues.

*/

#include "kattisio.h"

#include <algorithm>
#include <cmath>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

long double solve_problem(const std::vector<Transaction> &transactions)
{
    long double output;
    long long num_stocks = 0;
    long double average_buy_cost_per_stock = 0;

    for (const Transaction &transaction : transactions)
    {
        // could also use switch statement, but then would have to cast type to int. I prefer this for readability.
        if (transaction.type == "buy")
        {
            if (num_stocks == 0)
            {
                average_buy_cost_per_stock = transaction.price;
            }
            else
            {
                long long greatest_common_divisor_stocks = std::__gcd(num_stocks, transaction.num_stocks);
                average_buy_cost_per_stock =
                    ((num_stocks / greatest_common_divisor_stocks) * average_buy_cost_per_stock +
                     (transaction.num_stocks / greatest_common_divisor_stocks) * transaction.price) /
                    (num_stocks / greatest_common_divisor_stocks +
                     transaction.num_stocks / greatest_common_divisor_stocks);
            }
            num_stocks += transaction.num_stocks;
        }
        else if (transaction.type == "sell")
        {
            num_stocks -= transaction.num_stocks;
        }
        else if (transaction.type == "split")
        {
            num_stocks *= transaction.num_stocks;
            average_buy_cost_per_stock /= transaction.num_stocks;
        }
        else if (transaction.type == "merge")
        {
            num_stocks /= transaction.num_stocks;
            average_buy_cost_per_stock *= transaction.num_stocks;
        }
        else
        {
            long double profit_per_stock = transaction.price - average_buy_cost_per_stock;
            long double taxes_per_stock;
            if (profit_per_stock > 0)
            {
                taxes_per_stock = profit_per_stock * 0.3L;
            }
            else
            {
                taxes_per_stock = 0;
            }
            output = num_stocks * (transaction.price - taxes_per_stock);
        }
    }
    return output;
}