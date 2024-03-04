/*
----------------------------------------------------- PROBLEM -----------------------------------------------------



----------------------------------------------------- INPUT -----------------------------------------------------



----------------------------------------------------- OUTPUT -----------------------------------------------------



----------------------------------------------------- EXAMPLE -----------------------------------------------------



----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include "kattisio.h"

#include <cmath>
#include <limits>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <vector>

bool any_valid_numbers(int num_digits, int cross_sum)
{
    return num_digits * 9 >= cross_sum;
}

long long get_any_number(int num_digits, int cross_sum)
{
    std::string output = "";

    for (int i = 0; i < num_digits; i++)
    {
        if (cross_sum >= 9)
        {
            output += '9';
            cross_sum -= 9;
        }
        else
        {
            output += std::to_string(cross_sum);
            cross_sum = 0;
        }
    }

    return std::stoll(output);
}

int get_digit(long long num, int digit_pos)
{
    long long divisor = 1;
    for (int i = 0; i < digit_pos; i++)
    {
        divisor *= 10;
    }

    return (num / divisor) % 10;
}

std::tuple<long long, long long> find_num_valid_numbers(long long interval_start, long long interval_end,
                                                        int num_digits, int cross_sum)
{
    std::unordered_map<long long, bool> visited;
    std::queue<long long> queue;
    queue.emplace(get_any_number(num_digits, cross_sum));
    visited[queue.front()] = true;
    long long num_valid_numbers = 0;
    long long min_valid_numbers = std::numeric_limits<long long>::max();

    while (!queue.empty())
    {
        long long cur = queue.front();
        queue.pop();
        if (cur >= interval_start && cur <= interval_end)
        {
            num_valid_numbers++;
            if (cur < min_valid_numbers)
            {
                min_valid_numbers = cur;
            }
        }

        long long multiplier_add = 1;
        for (int i = 0; i < num_digits; i++)
        {
            int ith_digit = get_digit(cur, i);
            if (ith_digit != 9)
            {
                long long multiplier_subtract = 1;
                for (int j = 0; j < num_digits; j++)
                {
                    int jth_digit = get_digit(cur, j);
                    if (jth_digit != 0 && (j != num_digits - 1 || jth_digit > 1) && i != j)
                    {
                        long long new_num = cur + multiplier_add - multiplier_subtract;
                        if (visited.find(new_num) == visited.end())
                        {
                            queue.emplace(new_num);
                            visited[new_num] = true;
                        }
                    }
                    multiplier_subtract *= 10L;
                }
            }
            multiplier_add *= 10L;
        }
    }

    return std::tuple{num_valid_numbers, min_valid_numbers};
}

std::tuple<long long, long long> solve_problem(long long interval_start, long long interval_end, int cross_sum)
{
    long long lowest_number = std::numeric_limits<long long>::max();
    long long num_numbers = 0;

    int num_digits_interval_start = std::to_string(interval_start).length();
    int num_digits_interval_end = std::to_string(interval_end).length();

    for (int i = num_digits_interval_start; i <= num_digits_interval_end; i++)
    {
        if (any_valid_numbers(i, cross_sum))
        {
            std::tuple<long long, long long> temp = find_num_valid_numbers(interval_start, interval_end, i, cross_sum);
            num_numbers += std::get<0>(temp);
            if (std::get<1>(temp) < lowest_number)
            {
                lowest_number = std::get<1>(temp);
            }
        }
    }

    return std::tuple{num_numbers, lowest_number};
}