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


*/

#include "hashing.h"

#include <string>
#include <vector>

int solve_problem(const std::string &text)
{
    int max_power = 0;

    Polynomial_Hash_Family p = Polynomial_Hash_Family(text);

    for (int i = 1; i < text.size() - 2; i++)
    {
        int left = i;
        int right = i + 1;
        // set the split of w w_r | w w_r between position i and i+1 and extend it to the left and right, as long as the
        // characters match
        while (left >= 0 && right < text.size() && text[left] == text[right])
        {
            left--;
            right++;
        }

        // substring in question must be of size that is a multiple of 4
        if ((right - left) % 4 == 1)
        {
            left++;
            right--;
        }

        while (left < right && right - left > max_power)
        {
            // check if hash of first 1/4th equals that of 3/4
            // and 2/4 equals 4/4 (part)
        }
    }

    return max_power;
}