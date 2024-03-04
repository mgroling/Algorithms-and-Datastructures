/*
----------------------------------------------------- PROBLEM -----------------------------------------------------



----------------------------------------------------- INPUT -----------------------------------------------------



----------------------------------------------------- OUTPUT -----------------------------------------------------



----------------------------------------------------- EXAMPLE -----------------------------------------------------



----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include "kattisio.h"

#include <cmath>
#include <tuple>
#include <vector>

int calc_cross_sum(long long num)
{
    int sum = 0;
    while (num > 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

long long find_smallest_in_bounds(long long interval_start, long long interval_end, int cross_sum)
{
    int cross_sum_interval_start = calc_cross_sum(interval_start);
    if (cross_sum_interval_start == cross_sum)
    {
        return interval_start;
    }
    std::string interval_start_string = std::to_string(interval_start);
    long long remainder = cross_sum - cross_sum_interval_start;
    long long scale_factor = 1;
    int i = 0;

    while (remainder != 0)
    {
        long long digit;
        int index = interval_start_string.length() - 1 - i;
        if (index >= 0)
        {
            digit = std::stoll(std::string(1, interval_start_string[index]));
        }
        else
        {
            digit = 0;
        }

        int sub_remainder = std::min(9L - digit, remainder);

        interval_start += sub_remainder * scale_factor;
        remainder -= sub_remainder;
        scale_factor *= 10;
        i++;
    }

    return interval_start;
}

std::vector<std::vector<long long>> find_appearances(long long num, int num_digits)
{
    std::vector<long long> num_appearances(num_digits * 9 + 1, 0);
    std::vector<long long> num_appearances_critical(num_digits * 9 + 1, 0);

    for (int i = 0; i <= num; i++)
    {
        num_appearances[calc_cross_sum(i)]++;
    }

    for (int i = num + 1; i < std::pow(10, num_digits); i++)
    {
        num_appearances_critical[calc_cross_sum(i)]++;
    }

    return std::vector{num_appearances, num_appearances_critical};
}

std::vector<int> split_number(int num)
{
    std::vector<int> result(4, num / 4);
    int remainder = num % 4;
    for (int i = 0; i < remainder; i++)
    {
        result[i] += 1;
    }
    return result;
}

long long find_num_valid(long long interval_end, int cross_sum)
{
    std::string string_interval_end = std::to_string(interval_end);
    int num_digts = string_interval_end.length();
    if (num_digts < 6)
    {
        return find_appearances(interval_end, num_digts)[0][cross_sum];
    }

    long long num_valid = 0;
    std::vector<int> split = split_number(num_digts);
    int part1_num_digits = split[0];
    int part2_num_digits = split[1];
    int part3_num_digits = split[2];
    int part4_num_digits = split[3];
    long long part1_num = std::stoll(string_interval_end.substr(0, part1_num_digits));
    long long part2_num = std::stoll(string_interval_end.substr(part1_num_digits, part2_num_digits));
    long long part3_num = std::stoll(string_interval_end.substr(part1_num_digits + part2_num_digits, part3_num_digits));
    long long part4_num = std::stoll(
        string_interval_end.substr(part1_num_digits + part2_num_digits + part3_num_digits, part4_num_digits));
    long long cross_sum_num1 = calc_cross_sum(part1_num);
    long long cross_sum_num2 = calc_cross_sum(part2_num);
    long long cross_sum_num3 = calc_cross_sum(part3_num);

    std::vector<std::vector<long long>> appearances_part1 = find_appearances(part1_num, part1_num_digits);
    std::vector<std::vector<long long>> appearances_part2 = find_appearances(part2_num, part2_num_digits);
    std::vector<std::vector<long long>> appearances_part3 = find_appearances(part3_num, part3_num_digits);
    std::vector<std::vector<long long>> appearances_part4 = find_appearances(part4_num, part4_num_digits);

    for (int i = 0; i <= std::min(part1_num_digits * 9, cross_sum); i++)
    {
        for (int j = 0; j <= std::min(part2_num_digits * 9, cross_sum - i); j++)
        {
            for (int k = 0; k <= std::min(part3_num_digits * 9, cross_sum - i - j); k++)
            {
                int l = cross_sum - i - j - k;
                if (l > part4_num_digits * 9)
                {
                    continue;
                }

                num_valid += appearances_part1[0][i] * (appearances_part2[0][j] + appearances_part2[1][j]) *
                             (appearances_part3[0][k] + appearances_part3[1][k]) *
                             (appearances_part4[0][l] + appearances_part4[1][l]);

                if (cross_sum_num1 == i)
                {
                    num_valid -= appearances_part2[1][j] * (appearances_part3[0][k] + appearances_part3[1][k]) *
                                 (appearances_part4[0][l] + appearances_part4[1][l]);

                    if (cross_sum_num2 == j)
                    {
                        num_valid -= appearances_part3[1][k] * (appearances_part4[0][l] + appearances_part4[1][l]);

                        if (cross_sum_num3 == k)
                        {
                            num_valid -= appearances_part4[1][l];
                        }
                    }
                }
            }
        }
    }

    return num_valid;
}

std::tuple<long long, long long> solve_problem(long long interval_start, long long interval_end, int cross_sum)
{
    long long num_appearances_start = find_num_valid(interval_start, cross_sum);
    long long num_appearances_end = find_num_valid(interval_end, cross_sum);

    return std::tuple{num_appearances_end - num_appearances_start,
                      find_smallest_in_bounds(interval_start, interval_end, cross_sum)};
}