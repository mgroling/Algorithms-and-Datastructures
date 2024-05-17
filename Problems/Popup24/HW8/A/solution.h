/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

bool raise_by_one(std::string &price, std::unordered_map<char, int> &digits_required)
{
    int i = price.size() - 1;
    while (i >= 0)
    {
        if (price[i] != '9')
        {
            digits_required[price[i]]--;
            price[i]++;
            digits_required[price[i]]++;
            return true;
        }
        else
        {
            digits_required['9']--;
            price[i] = '0';
            digits_required['0']++;
        }
        i--;
    }
    return false;
}

std::string solve_test_case_naive(std::string price)
{
    std::string original_price = price;
    std::unordered_map<char, int> digits_available{{'0', 0}, {'1', 0}, {'2', 0}, {'3', 0}, {'4', 0},
                                                   {'5', 0}, {'6', 0}, {'7', 0}, {'8', 0}, {'9', 0}};
    for (const char &elem : price)
    {
        digits_available[elem]++;
    }
    std::unordered_map<char, int> digits_required = digits_available;

    bool next_available = true;
    while (next_available)
    {
        next_available = raise_by_one(price, digits_required);
        bool cond108 = digits_available['0'] + digits_available['1'] + digits_available['8'] ==
                       digits_required['0'] + digits_required['1'] + digits_required['8'];
        bool cond69 = digits_available['6'] + digits_available['9'] == digits_required['6'] + digits_required['9'];
        bool cond25 = digits_available['2'] + digits_available['5'] == digits_required['2'] + digits_required['5'];
        bool cond = digits_available['3'] == digits_required['3'] && digits_available['4'] == digits_required['4'] &&
                    digits_available['7'] == digits_required['7'];
        if (cond && cond108 && cond25 && cond69 && price > original_price)
        {
            return price.substr(0, price.size() - 1) + '.' + price.back();
        }
    }
    return "The price cannot be raised";
}

std::string solve_test_case(std::string price)
{
    std::unordered_map<char, char> increase_by_one = {{'6', '9'}, {'0', '1'}, {'1', '8'}, {'2', '5'}};
    std::unordered_map<char, char> lower_by_max = {{'9', '6'}, {'8', '0'}, {'1', '0'}, {'5', '2'}};
    std::unordered_map<char, char> lower_by_one = {{'9', '6'}, {'8', '1'}, {'1', '0'}, {'5', '2'}};

    std::string price_copy = price;

    bool price_changed = false;
    // find right-most position to make the number smaller by flipping numbers
    for (int i = price.size() - 1; i >= 0; i--)
    {
        auto ptr = increase_by_one.find(price[i]);
        // found a number that we can flip and make it bigger
        if (ptr != increase_by_one.end())
        {
            price_changed = true;
            price[i] = ptr->second;

            // flip
            for (int j = i + 1; j < price.size(); j++)
            {
                ptr = lower_by_max.find(price[j]);
                if (ptr != lower_by_max.end())
                {
                    price[j] = ptr->second;
                }
            }

            // sort
            std::sort(price.begin() + i + 1, price.end());
            break;
        }
    }

    bool price_copy_changed = false;
    // find right-most position to make the number smaller by swapping numbers
    for (int i = price_copy.size() - 1; i > 0; i--)
    {
        if (price_copy[i - 1] < price_copy[i])
        {
            price_copy_changed = true;
            // check if we can find a price[i - 1] + 1, +2, +3, etc.
            bool found = false;
            for (char c = price_copy[i - 1] + 1; c <= 57; c++)
            {
                for (int j = i; j < price_copy.size(); j++)
                {
                    if ((c == '0' || c == '1' || c == '8') &&
                        (price_copy[j] == '0' || price_copy[j] == '1' || price_copy[j] == '8'))
                    {
                        price_copy[j] = c;
                    }
                    else if ((c == '6' || c == '9') && (price_copy[j] == '6' || price_copy[j] == '9'))
                    {
                        price_copy[j] = c;
                    }
                    else if ((c == '2' || c == '5') && (price_copy[j] == '2' || price_copy[j] == '5'))
                    {
                        price_copy[j] = c;
                    }

                    if (price_copy[j] == c)
                    {
                        // swap price_copy[i - 1] with price_copy[j]
                        price_copy[j] = price_copy[i - 1];
                        price_copy[i - 1] = c;
                        found = true;
                        break;
                    }
                }

                if (found)
                {
                    break;
                }
            }

            // flip
            for (int j = i; j < price_copy.size(); j++)
            {
                auto ptr = lower_by_max.find(price_copy[j]);
                if (ptr != lower_by_max.end())
                {
                    price_copy[j] = ptr->second;
                }
            }

            // sort
            std::sort(price_copy.begin() + i, price_copy.end());
            break;
        }
    }

    std::string final_price;
    if (!price_changed && !price_copy_changed)
    {
        return "The price cannot be raised";
    }
    else if (price_changed && price_copy_changed)
    {
        final_price = std::min(price, price_copy);
    }
    else if (price_changed)
    {
        final_price = price;
    }
    else
    {
        final_price = price_copy;
    }

    return final_price.substr(0, final_price.size() - 1) + '.' + final_price[final_price.size() - 1];
}

std::vector<std::string> solve_problem(std::vector<std::string> &input)
{
    std::vector<std::string> output;

    for (std::string &test_case : input)
    {
        output.emplace_back(solve_test_case(test_case));
    }

    return output;
}
