/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

Casting spells is the least understood technique of dealing with real life. Actually, people find it quite hard to
distinguish between real spells like “abrahellehhelleh” (used in the battles and taught at the mage universities) and
screams like “rachelhellabracadabra” (used by uneducated witches for shouting at cats). Finally, the research conducted
at the Unheard University showed how one can measure the power of a word (be it a real spell or a scream). It appeared
that it is connected with the mages’ ability to pronounce words backwards. (Actually, some singers were burned at the
stake for exactly the same ability, as it was perceived as demonic possession.) Namely, the power of a word is the
length of the maximum subword of the form w w_r w w_r (where is w an arbitrary sequence of characters and w_r is w
written backwards). If no such subword exists, then the power of the word is 0. For example, the power of
abrahellehhelleh is 12 as it contains hellehhelleh and the power of rachelhellabracadabra is 0. Note that the power of a
word is always a multiple of 4.

----------------------------------------------------- INPUT -----------------------------------------------------

The input is a single line containing a word of length at most 3*10^5, consisting of (large or small) letters of the
English alphabet.

----------------------------------------------------- OUTPUT -----------------------------------------------------

You should output one integer k, the power of the word.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
abrahellehhelleh

Sample Output 1:
12

Sample Input 2:
rachelhellabracadabra

Sample Output 2:
0

----------------------------------------------------- SOLUTION -----------------------------------------------------

First notice one thing: if any string s = xy has the property that rev(x) = y and x = y, then s must have the form w w_r
w w_r. This makes it easier to search for a solution.

We can choose an arbitrary point in the string as the separator between x and y. Then we need to check for how long
rev(x) and y matches. Once we found a point where they no longer match, we can check if x = y, if that is not the case,
then we move the starting point of x 2 positions to the left and the end position of y 2 positions to the right and
repeat.

The power of the spell is the max power of any separator position.

*/

#include "hashing.h"

#include <algorithm>
#include <string>
#include <vector>

std::pair<int, int> position_in_reverse_string(const int &start, const int &end, const int &length_string)
{
    return {length_string - end, length_string - start};
}

void update_power(const std::string &text, const Polynomial_Hash_Family &p, const Polynomial_Hash_Family &p_rev,
                  const int &i, int &max_power)
{
    // split the word into two parts starting at position i and i + 1 (w w_r || w w_r)
    // notice that characters on both sides have to match going from i to the left and i+1 to the right
    int left = i;
    int right = i + 1;
    bool mismatch = false;
    // check that at least first 10 first characters to either side match (doing a binary search immediately is too
    // slow and in many cases unnecessary)
    for (int j = 0; j < 10; j++)
    {
        if (text[left] != text[right] || left == 0 || right == text.size() - 1)
        {
            mismatch = true;
            break;
        }
        left--;
        right++;
    }
    if (text[left] != text[right])
    {
        left++;
        right--;
    }

    if (!mismatch)
    {
        // do a binary search for how long characters match if we extend left and right
        int low = 9;
        int high = std::min(i, (int)text.size() - i + 1);
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            left = i - mid;
            right = i + 1 + mid;

            std::pair<int, int> rev_indices = position_in_reverse_string(i + 1, right + 1, text.size());
            if (p.get_hash(left, i + 1) == p_rev.get_hash(rev_indices.first, rev_indices.second))
            {
                // strings match exactly from left to right, but not after
                if (left - 1 < 0 || right + 1 == text.size() || text[left - 1] != text[right + 1])
                {
                    break;
                }
                else
                {
                    low = mid + 1;
                }
            }
            else
            {
                high = mid - 1;
            }
        }
    }

    // substring in question must be of size that is a multiple of 4
    if ((right - left) % 4 == 1)
    {
        left++;
        right--;
    }

    // substrings match from i to left == i+1 to right
    // now check that they also match from left to i == i+1 to right (cause then we have w w_r w w_r)
    while (left < right && (right - left) > max_power)
    {
        int middle = left + (right - left) / 2 + 1;
        if (p.get_hash(left, middle) == p.get_hash(middle, right + 1))
        {
            max_power = right - left + 1;
            return;
        }
        left += 2;
        right -= 2;
    }
}

int solve_problem(const std::string &text)
{
    Polynomial_Hash_Family p = Polynomial_Hash_Family(text);
    std::string text_rev = text;
    std::reverse(text_rev.begin(), text_rev.end());
    Polynomial_Hash_Family p_rev = Polynomial_Hash_Family(text_rev);

    int middle = (text.size() + 1) / 2 - 1;
    int max_power = 0;
    update_power(text, p, p_rev, middle, max_power);
    for (int i = 1; i < text.size() / 2 - 1; i++)
    {
        // too close to either end to obtain a higher power than the one already found
        if (max_power > (text.size() / 2 - i) * 2)
        {
            break;
        }

        // set the separator of w w_r || w w_r one step away from the middle one at a time
        update_power(text, p, p_rev, middle - i, max_power);
        update_power(text, p, p_rev, middle + i, max_power);
    }

    return max_power;
}