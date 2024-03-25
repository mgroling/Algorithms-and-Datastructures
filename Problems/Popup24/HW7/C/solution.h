/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

Pasijans, patience, or solitaire is the name for a group of single player card games. One new such game, so new it has
no name, is played with cards sporting random integers as values. The game starts by shuffling all cards and
distributing them in N sequences, not necessarily of equal length.

During each turn, the player can remove the first card in any sequence and place it at the end of the “Solution
sequence”. The card that was second in the selected sequence now becomes the first and the turn ends. Of course once the
card is in the “Solution sequence” it cannot be removed, replaced or altered in any way. So don’t even try.

The game ends when all cards are in the “Solution sequence”. The object of the game is to construct the best possible
“Solution sequence”. One sequence is better than the other if for the first cards they differ, lets call them X and Y,
the value on the card X is smaller than the value on the card Y.

Write a program that finds the best possible “Solution sequence”.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line contains one integer N (1 <= N <= 1000), the number of starting sequences.

The next N lines contain descriptions of input sequences. Each line starts with an integer L (1 <= L <= 1000), the
length of the sequence. It is followed by L positive integers, each at most 100 000 000.

----------------------------------------------------- OUTPUT -----------------------------------------------------

One line containing sum(L) numbers, the best possible “Solution sequence” obtainable.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
3
1 2
1 100
1 1

Sample Output 1:
1 2 100

Sample Input 2:
2
5 10 20 30 40 50
2 28 27

Sample Output 2:
10 20 28 27 30 40 50

Sample Input 3:
2
3 5 1 2
3 5 1 1

Sample Output 3:
5 1 1 5 1 2

----------------------------------------------------- SOLUTION -----------------------------------------------------

This problem seems very easy, except for the case that two sequences (or suffixes of these) have the same element in the
beginning. If that is the case, then one should extract elements from the one that is smaller (for the first number that
they differ, the one with the smaller one may be considered smaller).

Doing this each time a comparison is needed would take too much time. However, we can use the algorithm to create a
suffix array here. This way, we can order the suffixes of all sequences, which gives an easy way to define a comparator
function between the suffixes of two sequences. To efficiently get the card from the smallest sequence available, a
priority queue (binary heap) is used.

*/

#include <algorithm>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

// comparator for the initial sorting according to the first element of each sequence (and their suffixes).
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

    // insert elements with a non-empty suffix (longer sequences are better, so we insert these ones first before the
    // other ones below)
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

    // sort sequences (and their suffixes) by their first element
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
    // the sequence (this describes a suffix of a sequence)
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