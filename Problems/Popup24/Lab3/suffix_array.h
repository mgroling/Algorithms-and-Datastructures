// Authors: Marc Gröling

#ifndef suffix_array_h
#define suffix_array_h

#include <algorithm>
#include <string>
#include <vector>

struct CharacterComparator
{
    const std::string &str;

    CharacterComparator(const std::string &s) : str(s)
    {
    }

    bool operator()(int a, int b) const
    {
        return str[a] < str[b];
    }
};

struct BucketComparator
{
    std::vector<int> buckets;
    int k;

    BucketComparator(const std::vector<int> &buckets, const int &k)
    {
        this->buckets = buckets;
        this->k = k >> 1;
    }

    bool operator()(int a, int b) const
    {
        if (a + k >= buckets.size())
        {
            return true;
        }
        else if (b + k >= buckets.size())
        {
            return false;
        }
        return buckets[a + k] < buckets[b + k];
    }
};

std::vector<int> create_suffix_array(std::string word)
{
    std::vector<int> suffix_array;
    suffix_array.reserve(word.size());
    for (int i = 0; i < word.size(); i++)
    {
        suffix_array.push_back(i);
    }
    // sort suffixes by their first character
    std::sort(suffix_array.begin(), suffix_array.end(), CharacterComparator(word));

    // now compute which bucket they belong to (characters with the same starting char belong to the same bucket)
    std::vector<int> corresponding_bucket(word.size());
    std::vector<int> bucket_sizes;
    bucket_sizes.push_back(1);
    corresponding_bucket[suffix_array[0]] = 0;
    int bucket = 0;
    for (int i = 1; i < suffix_array.size(); i++)
    {
        if (word[suffix_array[i]] != word[suffix_array[i - 1]])
        {
            bucket++;
            bucket_sizes.push_back(0);
        }
        corresponding_bucket[suffix_array[i]] = bucket;
        bucket_sizes.back()++;
    }

    // now use the information on the buckets to sort the array in exponential steps
    for (int k = 2; k < word.size(); k = k << 1)
    {
        BucketComparator comp = BucketComparator(corresponding_bucket, k);
        int offset = 0;
        // sort each bucket individually
        for (int i = 0; i < bucket_sizes.size(); i++)
        {
            std::sort(offset + suffix_array.begin(), offset + suffix_array.begin() + bucket_sizes[i], comp);
            offset += bucket_sizes[i];
        }

        // recompute corresponding buckets and bucket sizes arrays
        std::vector<int> corresponding_bucket_new(word.size());
        int k_halved = k >> 1;
        corresponding_bucket_new[suffix_array[0]] = 0;
        bucket = 0;
        bucket_sizes.clear();
        bucket_sizes.push_back(1);
        for (int i = 1; i < suffix_array.size(); i++)
        {
            int temp1 = suffix_array[i] + k_halved < corresponding_bucket.size()
                            ? corresponding_bucket[suffix_array[i] + k_halved]
                            : -1;
            int temp2 = suffix_array[i - 1] + k_halved < corresponding_bucket.size()
                            ? corresponding_bucket[suffix_array[i - 1] + k_halved]
                            : -2;
            if (temp1 != temp2)
            {
                bucket++;
                bucket_sizes.push_back(0);
            }
            corresponding_bucket_new[suffix_array[i]] = bucket;
            bucket_sizes.back()++;
        }
        corresponding_bucket = corresponding_bucket_new;

        // array is sorted if this is true
        if (corresponding_bucket.size() == word.size())
        {
            break;
        }
    }

    return suffix_array;
}

#endif