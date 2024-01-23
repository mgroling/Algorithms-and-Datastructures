/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

The magician shuffles a small pack of cards, holds it face down and performs the following procedure:

    1. The top card is moved to the bottom of the pack. The new top card is dealt face up onto the table. It is the Ace
of Spades.

    2. Two cards are moved one at a time from the top to the bottom. The next card is dealt face up onto the table. It
is the Two of Spades.

    3. Three cards are moved one at a time…

    4. This goes on until the n'th and last card turns out to be the n of Spades.

This impressive trick works if the magician knows how to arrange the cards beforehand (and knows how to give a false
shuffle). Your program has to determine the initial order of the cards for a given number of cards.

----------------------------------------------------- INPUT -----------------------------------------------------

On the first line of the input is a single positive integer T<=13 the number of test cases to follow. Each case consists
of one line containing the integer n (1<=n<=13).

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each test case, output a line with the correct permutation of the values 1 to n, space separated. The first number
showing the top card of the pack, etc…

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
2
4
5

Sample Output 1:
2 1 4 3
3 1 4 5 2

----------------------------------------------------- SOLUTION -----------------------------------------------------

We can solve the problem by working backwards. In the beginning, we only have one card. We notice, that the next card i
that we need to insert will be at position (i % num_cards_inserted), where num_cards_inserted corresponds to how many
cards we have added so far. Above card i, the bottom card of the previous iteration is placed and below card i, the top
card of the previous iteration is placed (and 2 above is the second card from the bottom and so on).

This example may help illustrate this (the stars mark the element that was just inserted):
3
1*      4
4       5       3*                     ARRAY
5       2*      4       4*
2       3       5       5       5*

1       2       0       0       0      (i % num_cards_inserted)
1%5     2%4     3%3     4%2     5%1    (calculation of it)

*/

#include "kattisio.h"

#include <vector>

std::vector<int> solve_test_case(const int &num_cards)
{
    std::vector<int> output;
    for (int i = num_cards; i > 0; i--)
    {
        int new_element_position = i % (output.size() + 1);
        std::vector<int> temp;
        temp.insert(temp.end(), output.end() - new_element_position, output.end());
        temp.push_back(i);
        temp.insert(temp.end(), output.begin(), output.end() - new_element_position);
        output = temp;
    }
    return output;
}

std::vector<std::vector<int>> solve_problem(const std::vector<int> &test_cases)
{
    std::vector<std::vector<int>> output;

    for (const int &num_cards : test_cases)
    {
        output.emplace_back(solve_test_case(num_cards));
    }

    return output;
}