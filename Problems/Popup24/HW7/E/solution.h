/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

A radio station needs to transmit a message to several recipients. To ensure all listeners get it, the message is played
again and again in a continuous loop.

You’re given a sequence of characters recieved by one of the recipients. It is known that the sequence is at least as
long as the message.

Your task is to write a program the extracts the message transmitted by the station. More formally, your program needs
to find the shortest subsring S' of the input string S such that in turn is a substring of the (sufficiently long)
repetition S' + S' + ... + S'.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line contains a single integer 1 <= L <= 1 000 000, the length of the string S. The second line contains
exactly L characters, the string S itself. The sequence consists of lowercase letters a-z.

----------------------------------------------------- OUTPUT -----------------------------------------------------

The program should write one line to standard output containing a single integer: the length L' of the message S'. Note
that L' must be the smallest possible. If there are multiple smallest L', you may output any of them.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
8
cabcabca

Sample Output 1:
3

The message could (among other options) be “abc”, “cab” or “abcabc”, but there is no possible message shorter than 3
characters.

----------------------------------------------------- SOLUTION -----------------------------------------------------

We can use the table building algorithm from the knuth-morris-pratt algorithm. The last entry of the table gives the
index to which we have to go back if we find a match. We can think of this as shitfting the pattern on the text. Then
the length of the word - last entry of kmp table will give us by how much we have to shift.

example: "cabcabca", if we find a complete match, then we have to "skip" the first "cab" to find another match, as such
the length of S' is 3.

*/

#include "substring_search.h"

#include <string>
#include <vector>

int solve_problem(const std::string &word)
{
    return word.size() - build_kmp_table(word).back();
}