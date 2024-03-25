// Authors: Marc Gröling
// Methods for general use: create_suffix_array
// Helper methods: counting_sort_initial, counting_sort

#ifndef suffix_array_h
#define suffix_array_h

#include <string>
#include <tuple>
#include <vector>

std::pair<std::vector<int>, std::vector<int>> counting_sort_initial(std::vector<int> &suffix_array,
                                                                    const std::string &word)
{
    // only sort by first char
    std::vector<std::vector<int>> count(256, std::vector<int>{});
    std::vector<int> corresponding_bucket(word.size());
    std::vector<int> bucket_start;

    for (int i = 0; i < suffix_array.size(); i++)
    {
        count[word[i]].push_back(suffix_array[i]);
    }

    int offset = 0;
    int bucket = -1;
    bucket_start.push_back(0);
    // compute bucket sizes and for each element which bucket it belongs to
    for (int i = 0; i < count.size(); i++)
    {
        if (count[i].size())
        {
            bucket++;
            bucket_start.push_back(count[i].size());
        }

        for (int j = 0; j < count[i].size(); j++)
        {
            suffix_array[offset++] = count[i][j];
            corresponding_bucket[count[i][j]] = bucket;
        }
    }

    // convert bucket sizes to the start of the bucket
    for (int i = 1; i < bucket_start.size(); i++)
    {
        bucket_start[i] += bucket_start[i - 1];
    }
    bucket_start.pop_back();

    return {corresponding_bucket, bucket_start};
}

std::vector<int> counting_sort(std::vector<int> &suffix_array, const int &k,
                               const std::vector<int> &corresponding_bucket, std::vector<int> &bucket_start)
{
    int n = suffix_array.size();
    std::vector<std::vector<int>> count(bucket_start.size(), std::vector<int>{});

    // insert elements into count that don't have an empty suffix (on the second k characters)
    for (int i = 0; i < n - k; i++)
    {
        count[corresponding_bucket[i + k]].push_back(i);
    }

    // insert elements with an empty suffix (on the last k characters) directly into the suffix array (in their buckets)
    // in reverse order, since "aa" < "aaa" (equal on first n characters, then the word with size n is always smaller)
    for (int i = n - 1; i >= n - k; i--)
    {
        suffix_array[bucket_start[corresponding_bucket[i]]] = i;
        // shift start of that bucket one place to the right
        bucket_start[corresponding_bucket[i]]++;
    }

    // insert elements with a non-empty suffix
    for (int i = 0; i < count.size(); i++)
    {
        for (int j = 0; j < count[i].size(); j++)
        {
            // get the bucket of that element and place it in the suffix array
            suffix_array[bucket_start[corresponding_bucket[count[i][j]]]] = count[i][j];
            // shift start of that bucket one place to the right
            bucket_start[corresponding_bucket[count[i][j]]]++;
        }
    }

    int bucket = 0;
    bucket_start.clear();
    bucket_start.push_back(bucket);
    std::vector<int> corresponding_bucket_new(suffix_array.size());
    corresponding_bucket_new[suffix_array[0]] = bucket;
    // recompute bucket information
    for (int i = 1; i < suffix_array.size(); i++)
    {
        int temp1 = suffix_array[i] + k < corresponding_bucket.size() ? corresponding_bucket[suffix_array[i] + k] : -1;
        int temp2 =
            suffix_array[i - 1] + k < corresponding_bucket.size() ? corresponding_bucket[suffix_array[i - 1] + k] : -2;
        // if either the first k characters are in a different bucket or the last k, then we create a new bucket
        if (corresponding_bucket[suffix_array[i]] != corresponding_bucket[suffix_array[i - 1]] || temp1 != temp2)
        {
            bucket++;
            bucket_start.push_back(i);
        }
        corresponding_bucket_new[suffix_array[i]] = bucket;
    }

    return corresponding_bucket_new;
}

std::vector<int> create_suffix_array(const std::string &word)
{
    std::vector<int> suffix_array;
    suffix_array.reserve(word.size());
    for (int i = 0; i < word.size(); i++)
    {
        suffix_array.push_back(i);
    }
    // sort suffixes by their first character and compute the corresponding bucket and the start index of each bucket
    std::vector<int> corresponding_bucket, bucket_start;
    std::tie(corresponding_bucket, bucket_start) = counting_sort_initial(suffix_array, word);

    // now use the information on the buckets to sort the array in exponential steps
    for (int k = 1; k < word.size(); k = k << 1)
    {
        // number of buckets equals number of elements => array is sorted
        if (bucket_start.size() == word.size())
        {
            break;
        }

        // the first k characters of the array are sorted, sort on the next k ones
        corresponding_bucket = counting_sort(suffix_array, k, corresponding_bucket, bucket_start);
    }

    return suffix_array;
}

#endif