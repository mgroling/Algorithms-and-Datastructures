/*
----------------------------------------------------- PROBLEM -----------------------------------------------------



----------------------------------------------------- INPUT -----------------------------------------------------



----------------------------------------------------- OUTPUT -----------------------------------------------------



----------------------------------------------------- EXAMPLE -----------------------------------------------------



----------------------------------------------------- SOLUTION -----------------------------------------------------

*/

#include "kattisio.h"

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
            average_buy_cost_per_stock =
                (num_stocks * average_buy_cost_per_stock + transaction.num_stocks * transaction.price) /
                (num_stocks + transaction.num_stocks);
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
                taxes_per_stock = profit_per_stock * 0.3;
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