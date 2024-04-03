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

bool raise_and_lower(std::string &string, const std::string &price)
{
    bool exists = false;
    std::unordered_map<char, char> lower_map = {{'9', '6'}, {'1', '0'}, {'8', '0'}, {'5', '2'}};
    std::unordered_map<char, char> raise_map = {{'6', '9'}, {'0', '1'}, {'1', '8'}, {'2', '5'}};
    for (int i = string.size() - 1; i >= 0; i--)
    {
        auto ptr = raise_map.find(string[i]);
        // digit to increase exists
        if (ptr != raise_map.end())
        {
            exists = true;
            string[i] = ptr->second;
            // now lower all digits after i
            for (int j = i + 1; j < string.size(); j++)
            {
                auto ptr2 = lower_map.find(string[j]);
                // key exists
                if (ptr2 != lower_map.end())
                {
                    string[j] = ptr2->second;
                }
            }

            // now we need to get previous permutations of the part until here until it is no longer greater than
            // the initial price
            bool lower_exists = true;
            while (string > price && lower_exists)
            {
                std::prev_permutation(string.begin() + i, string.end());
            }
            if (string <= price)
            {
                std::next_permutation(string.begin() + i, string.end());
            }

            break;
        }
    }

    return exists;
}

bool lower(std::string &string, const std::string &price)
{
    bool exists = false;
    std::unordered_map<char, char> lower_map = {{'9', '6'}, {'1', '0'}, {'8', '0'}, {'5', '2'}};

    bool lower_now = false;
    for (int i = 0; i < string.size(); i++)
    {
        if (string[i] > price[i])
        {
            auto ptr = lower_map.find(string[i]);
            if (ptr != lower_map.end() && ptr->second > price[i])
            {
                string[i] = ptr->second;
            }
            lower_now = true;
            continue;
        }
        if (lower_now)
        {
            auto ptr = lower_map.find(string[i]);
            if (ptr != lower_map.end())
            {
                string[i] = ptr->second;
                exists = true;
            }
        }
    }

    bool lower_exists = true;
    while (string > price && lower_exists)
    {
        std::prev_permutation(string.begin(), string.end());
    }
    if (string <= price)
    {
        std::next_permutation(string.begin(), string.end());
    }

    return exists;
}

std::string solve_test_case(std::string price)
{
    std::string next_perm_strat = price;
    bool next_perm_exists = std::next_permutation(next_perm_strat.begin(), next_perm_strat.end());

    std::string next_raise_strat = next_perm_strat;
    bool next_raise_perm_exists = lower(next_raise_strat, price) && next_perm_exists;

    std::string raise_strat = price;
    bool raise_perm_exists = raise_and_lower(raise_strat, price);

    std::string return_value = "";
    if (next_perm_exists)
    {
        return_value = next_perm_strat;
    }
    if (next_raise_perm_exists && (return_value == "" || next_raise_strat < return_value))
    {
        return_value = next_raise_strat;
    }
    if (raise_perm_exists && (return_value == "" || raise_strat < return_value))
    {
        return_value = raise_strat;
    }

    if (return_value == "")
    {
        return "The price cannot be raised";
    }
    return return_value.substr(0, return_value.size() - 1) + '.' + return_value.back();
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
        if (cond && cond108 && cond25 && cond69)
        {
            return price.substr(0, price.size() - 1) + '.' + price.back();
        }
    }
    return "The price cannot be raised";
}