/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

The Burrows-Wheeler transform is a technique for transforming a text message so that it responds well to compression
techniques. Under this transform, we consider all cyclic shifts of an input string. For example, if our text was the
string “arbitrary string”, then the string “rbitrary stringa” would be the result of cyclicly shifting the string one
character to the left. The first character is moved to the end of the string, and all of the other characters are moved
one index earlier. If a string has n characters, then there are n cyclic shifts of the string. The text on the left
lists all cyclic shifts of the string “arbitrary string”, one per line.

arbitrary string                               stringarbitrary
rbitrary stringa                              arbitrary string
bitrary stringar                              ary stringarbitr
itrary stringarb                              bitrary stringar
trary stringarbi                              garbitrary strin
rary stringarbit                              ingarbitrary str
ary stringarbitr                              itrary stringarb
ry stringarbitra                              ngarbitrary stri
y stringarbitrar                              rary stringarbit
 stringarbitrary                              rbitrary stringa
stringarbitrary                               ringarbitrary st
tringarbitrary s                              ry stringarbitra
ringarbitrary st                              stringarbitrary
ingarbitrary str                              trary stringarbi
ngarbitrary stri                              tringarbitrary s
garbitrary strin                              y stringarbitrar

Under the Burrows-Wheeler transform, we imagine that we lexicographically sorted all these lines. The figure on the
right illustrates what this would yield for the text “arbitrary string”. The original message is encoded as the
right-hand column of this sorted list of cyclicly shifted copies of the input string. For example, “arbitrary string”
would be encoded as “ygrrnrbitata isr”. (take the last character of the column on the right from top to bottom)

For this problem, you are expected to compute the Burrows-Wheeler transform for an arbitrary line of text. Of course,
the transform is invertible, but we’ll let some other programmer worry about recovering the original message from your
encoding.

----------------------------------------------------- INPUT -----------------------------------------------------

Input consists of up to 100 messages, one per line. A message may use lowercase or uppercase letters (a–z), digits,
punctuation, and spaces. Each message may be up to 100 000 characters in length. Messages continue up to the end of
file. The total number of input characters is no more than 2^20.

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each input message, output a single line that results from applying the Burrows-Wheeler transform. The validation
for this problem is sensitive to both case and spacing changes.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
arbitrary string
this is the thing I was talking about

Sample Output 2:
ygrrnrbitata isr
ggssseI  twahnnttthkh laiibiai   tuo

----------------------------------------------------- SOLUTION -----------------------------------------------------

To get the sorted array of cyclic shifts, we can use an algorithm similar to creating a suffix array: we first sort the
cyclic shifts by their first character, then by their 2^1, 2^2, ..., 2^(log_2(n)) characters. In each iteration, we can
use the progress of the last iteration to determine how we should sort the next characters.

Notice that in the construction for a suffix array, different suffixes have different lengths, while here they all have
the same length. (so we can just use modulo n to determine which bucket to use)

*/

#include <string>
#include <tuple>
#include <vector>

std::pair<std::vector<int>, std::vector<int>> counting_sort_initial(std::vector<int> &shifts_array,
                                                                    const std::string &word)
{
    // only sort by first char
    std::vector<std::vector<int>> count(256, std::vector<int>{});
    std::vector<int> corresponding_bucket(word.size());
    std::vector<int> bucket_start;

    for (int i = 0; i < shifts_array.size(); i++)
    {
        count[word[i]].push_back(shifts_array[i]);
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
            shifts_array[offset++] = count[i][j];
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

std::vector<int> counting_sort(std::vector<int> &shifts_array, const int &k,
                               const std::vector<int> &corresponding_bucket, std::vector<int> &bucket_start)
{
    // basically the same code as for creating a suffix array, but here all "suffixes" are of size n
    int n = shifts_array.size();
    std::vector<std::vector<int>> count(bucket_start.size(), std::vector<int>{});

    // insert elements into count according to which bucket they are in
    for (int i = 0; i < n; i++)
    {
        // this is the string cycled i times and looking at it from the starting position k
        count[corresponding_bucket[(i + k) % corresponding_bucket.size()]].push_back(i);
    }

    // insert elements into the shifts array again
    for (int i = 0; i < count.size(); i++)
    {
        for (int j = 0; j < count[i].size(); j++)
        {
            // get the bucket of that element and place it in the suffix array
            shifts_array[bucket_start[corresponding_bucket[count[i][j]]]] = count[i][j];
            // shift start of that bucket one place to the right
            bucket_start[corresponding_bucket[count[i][j]]]++;
        }
    }

    int bucket = 0;
    bucket_start.clear();
    bucket_start.push_back(bucket);
    std::vector<int> corresponding_bucket_new(shifts_array.size());
    corresponding_bucket_new[shifts_array[0]] = bucket;
    // recompute bucket information
    for (int i = 1; i < shifts_array.size(); i++)
    {
        int temp1 = corresponding_bucket[(shifts_array[i] + k) % corresponding_bucket.size()];
        int temp2 = corresponding_bucket[(shifts_array[i - 1] + k) % corresponding_bucket.size()];
        // if either the first k characters are in a different bucket or the last k, then we create a new bucket
        if (corresponding_bucket[shifts_array[i]] != corresponding_bucket[shifts_array[i - 1]] || temp1 != temp2)
        {
            bucket++;
            bucket_start.push_back(i);
        }
        corresponding_bucket_new[shifts_array[i]] = bucket;
    }

    return corresponding_bucket_new;
}

std::vector<int> create_cyclic_shifts_array(const std::string &word)
{
    std::vector<int> shifts_array;
    shifts_array.reserve(word.size());
    for (int i = 0; i < word.size(); i++)
    {
        shifts_array.push_back(i);
    }
    // sort suffixes by their first character and compute the corresponding bucket and the start index of each bucket
    std::vector<int> corresponding_bucket, bucket_start;
    std::tie(corresponding_bucket, bucket_start) = counting_sort_initial(shifts_array, word);

    // now use the information on the buckets to sort the array in exponential steps
    for (int k = 1; k < word.size(); k = k << 1)
    {
        // the first k characters of the array are sorted, sort on the next k ones
        corresponding_bucket = counting_sort(shifts_array, k, corresponding_bucket, bucket_start);

        // number of buckets equals number of elements => array is sorted
        if (bucket_start.size() == word.size())
        {
            break;
        }
    }

    return shifts_array;
}

std::string burrows_wheeler_transform(const std::string &text)
{
    std::string output;
    std::vector<int> sorted_cyclic_shifts_array = create_cyclic_shifts_array(text);

    for (int i = 0; i < sorted_cyclic_shifts_array.size(); i++)
    {
        output += text[(sorted_cyclic_shifts_array[i] + text.size() - 1) % text.size()];
    }

    return output;
}

std::vector<std::string> solve_problem(const std::vector<std::string> &input)
{
    std::vector<std::string> transformed_text;

    for (const std::string &text : input)
    {
        transformed_text.emplace_back(burrows_wheeler_transform(text));
    }

    return transformed_text;
}