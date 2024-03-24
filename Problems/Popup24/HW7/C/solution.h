/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include <algorithm>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

struct SequenceComparator
{
    const std::vector<std::vector<int>> *sequences;

    SequenceComparator(const std::vector<std::vector<int>> *sequences)
    {
        this->sequences = sequences;
    }

    bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) const
    {
        return (*sequences)[a.first][a.second] < (*sequences)[b.first][b.second];
    }
};

int elem_to_id(std::pair<int, int> elem, int num_elems)
{
    return elem.second * num_elems + elem.first;
}

std::unordered_map<int, int> counting_sort(std::vector<std::pair<int, int>> &suffix_array, const int &k,
                                           const std::unordered_map<int, int> &corresponding_bucket,
                                           std::vector<int> &bucket_start,
                                           const std::vector<std::vector<int>> &sequences)
{
    std::vector<std::vector<std::pair<int, int>>> count(bucket_start.size(), std::vector<std::pair<int, int>>{});

    // insert elements into count that don't have an empty suffix (on the second k characters)
    for (int i = 0; i < sequences.size(); i++)
    {
        for (int j = 0; j < (int)(sequences[i].size() - k); j++)
        {
            int index = elem_to_id({i, j}, sequences.size()) + k * sequences.size();
            int bucket = corresponding_bucket.at(i + (j + k) * sequences.size());
            count[corresponding_bucket.at(elem_to_id({i, j}, sequences.size()) + k * sequences.size())].emplace_back(i,
                                                                                                                     j);
        }
    }

    // insert elements with a non-empty suffix
    for (int i = 0; i < count.size(); i++)
    {
        for (int j = 0; j < count[i].size(); j++)
        {
            // get the bucket of that element and place it in the suffix array
            suffix_array[bucket_start[corresponding_bucket.at(elem_to_id(count[i][j], sequences.size()))]] =
                count[i][j];
            // shift start of that bucket one place to the right
            bucket_start[corresponding_bucket.at(elem_to_id(count[i][j], sequences.size()))]++;
        }
    }

    // insert elements with an empty suffix (on the last k characters) directly into the suffix array (in their buckets)
    // in normal order, since [2, 3, 1] < [2, 3] (equal on first n characters, then the word with size n is always
    // greater)
    for (int i = 0; i < sequences.size(); i++)
    {
        for (int j = sequences[i].size() - k; j < sequences[i].size(); j++)
        {
            suffix_array[bucket_start[corresponding_bucket.at(elem_to_id({i, j}, sequences.size()))]] = {i, j};
            bucket_start[corresponding_bucket.at(elem_to_id({i, j}, sequences.size()))]++;
        }
    }

    int bucket = 0;
    std::unordered_map<int, int> corresponding_bucket_new;
    corresponding_bucket_new[elem_to_id(suffix_array[0], sequences.size())] = bucket;
    bucket_start.clear();
    bucket_start.push_back(bucket);
    // recompute bucket information
    for (int i = 1; i < suffix_array.size(); i++)
    {
        int temp1 = suffix_array[i].second + k < sequences[suffix_array[i].first].size()
                        ? corresponding_bucket.at(elem_to_id(suffix_array[i], sequences.size()) + k * sequences.size())
                        : -1;
        int temp2 =
            suffix_array[i - 1].second + k < sequences[suffix_array[i - 1].first].size()
                ? corresponding_bucket.at(elem_to_id(suffix_array[i - 1], sequences.size()) + k * sequences.size())
                : -2;
        // if either the first k characters are in a different bucket or the last k, then we create a new
        // bucket
        if (corresponding_bucket.at(elem_to_id(suffix_array[i], sequences.size())) !=
                corresponding_bucket.at(elem_to_id(suffix_array[i - 1], sequences.size())) ||
            temp1 != temp2)
        {
            bucket++;
            bucket_start.push_back(i);
        }
        corresponding_bucket_new[elem_to_id(suffix_array[i], sequences.size())] = bucket;
    }

    return corresponding_bucket_new;
}

std::unordered_map<int, int> create_suffix_array(const std::vector<std::vector<int>> &sequences)
{
    int num_elems = 0;
    int num_sequences = sequences.size();
    int max_sequence_length = 0;
    // first element is sequence, second is start index of suffix
    std::vector<std::pair<int, int>> suffix_array;
    for (int i = 0; i < num_sequences; i++)
    {
        for (int j = 0; j < sequences[i].size(); j++)
        {
            suffix_array.emplace_back(i, j);
        }
        num_elems += sequences[i].size();
        max_sequence_length = std::max(max_sequence_length, (int)sequences[i].size());
    }

    // sort sequences (suffixes) by their first element
    std::sort(suffix_array.begin(), suffix_array.end(), SequenceComparator(&sequences));

    // compute the corresponding bucket and the start index of each bucket
    int bucket = 0;
    std::unordered_map<int, int> corresponding_bucket;
    corresponding_bucket[elem_to_id(suffix_array[0], num_sequences)] = bucket;
    std::vector<int> bucket_start;
    bucket_start.push_back(bucket);
    for (int i = 1; i < suffix_array.size(); i++)
    {
        // if the sequences have different starting elements, then add new bucket
        if (sequences[suffix_array[i].first][suffix_array[i].second] !=
            sequences[suffix_array[i - 1].first][suffix_array[i - 1].second])
        {
            bucket++;
            bucket_start.push_back(i);
        }
        corresponding_bucket[elem_to_id(suffix_array[i], num_sequences)] = bucket;
    }

    // now use the information on the buckets to sort the array in exponential steps
    for (int k = 1; k < max_sequence_length; k = k << 1)
    {
        // number of buckets equals number of elements => array is sorted
        if (bucket_start.size() == num_elems)
        {
            break;
        }

        // the first k characters of the array are sorted, sort on the next k ones
        corresponding_bucket = counting_sort(suffix_array, k, corresponding_bucket, bucket_start, sequences);
    }

    // return the mapping from element to bucket for easy comparisons between sequences
    return corresponding_bucket;
}

struct CustomComparator
{
    const std::unordered_map<int, int> *corresponding_bucket;
    int num_elems;

    CustomComparator(const std::unordered_map<int, int> *corresponding_bucket, const int &num_elems)
    {
        this->corresponding_bucket = corresponding_bucket;
        this->num_elems = num_elems;
    }

    bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) const
    {
        return corresponding_bucket->at(elem_to_id(a, num_elems)) > corresponding_bucket->at(elem_to_id(b, num_elems));
    }
};

std::vector<int> solve_problem(std::vector<std::vector<int>> &problem)
{
    std::unordered_map<int, int> corresponding_bucket = create_suffix_array(problem);
    // first elem of pair is the index of the sequences that the element is from and the second value is the index in
    // the sequence
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, CustomComparator> sequence_pq(
        CustomComparator(&corresponding_bucket, problem.size()));
    // index of next element that is not yet in the priority queue
    std::vector<int> index(problem.size(), 1);

    for (int i = 0; i < problem.size(); i++)
    {
        sequence_pq.emplace(i, 0);
    }

    std::vector<int> output;
    while (!sequence_pq.empty())
    {
        std::pair<int, int> elem = sequence_pq.top();
        sequence_pq.pop();

        output.push_back(problem[elem.first][elem.second]);
        // insert next value from that card stack
        if (index[elem.first] < problem[elem.first].size())
        {
            sequence_pq.emplace(elem.first, index[elem.first]);
            index[elem.first]++;
        }
    }

    return output;
}