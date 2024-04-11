#include <algorithm>
#include <string>
#include <vector>

#include "suffix_array.h"

std::vector<int> solve_problem(const Test_case &test_case)
{
    std::vector<int> output;

    std::pair<std::vector<int>, std::vector<int>> suffix_array = create_suffix_array(test_case.sentence);
    std::vector<int> lcp_array = create_longest_common_prefix_array(suffix_array.first, test_case.sentence);

    std::vector<std::pair<int, int>> lcp_array_windex;
    for (int i = 0; i < lcp_array.size(); i++)
    {
        lcp_array_windex.emplace_back(lcp_array[i], i);
    }
    std::sort(lcp_array_windex.begin(), lcp_array_windex.end(),
              [](auto const &lhs, auto const &rhs) { return lhs.first < rhs.first; });

    for (const std::pair<int, int> query : test_case.queries)
    {
        int index_1 = suffix_array.second[query.first];
        int index_2 = suffix_array.second[query.second];

        int min_index = std::min(index_1, index_2);
        int max_index = std::max(index_1, index_2);

        int lcp;

        if (max_index - min_index < 100)
        {
            lcp = lcp_array[min_index + 1];
            for (int i = min_index + 2; i <= max_index; i++)
            {
                lcp = std::min(lcp, lcp_array[i]);
            }
        }
        else
        {
            for (int i = 0; i < lcp_array_windex.size(); i++)
            {
                if (lcp_array_windex[i].second > min_index && lcp_array_windex[i].second <= max_index)
                {
                    lcp = lcp_array_windex[i].first;
                    break;
                }
            }
        }

        output.push_back(lcp);
    }

    return output;
}