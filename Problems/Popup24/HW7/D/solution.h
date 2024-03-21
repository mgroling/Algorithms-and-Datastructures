/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

Mirko’s ASCII street is made of N lowercase letters of the English alphabet. The city government occasionally replaces
the tiles in the street. However, the letter tiles are in high demand, so the government has only M different tile
patterns available.

The i'th tile pattern consists of L_i letters. A tile cannot be rotated or broken into pieces, and it can only be placed
such that the tile letters coincide with the contiguous letter subsequence in the street. Tiles can overlap and we can
use multiple tiles of the same pattern.

A street cell is untileable if it cannot be covered by any tile. Compute the number of untileable cells.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line of input contains the positive integer N (1 <= N <= 300 000), the length of the street.

The second line of input contains N lowercase English letters, the letter sequence in the street.

The third line of input contains the positive integer M (1 <= M <= 5000), the number of tile patterns.

Each of the next M lines contains a description of a tile pattern with length L_i (1 <= L_i <= 5000). The tile pattern
descriptions consist of lowercase English letters.

The total length of the tile patterns (the sum of the L_i's) is at most 13 000 000.

----------------------------------------------------- OUTPUT -----------------------------------------------------

The first and only line of output must contain the required number of untileable cells.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
6
abcbab
2
cb
cbab

Sample Output 1:
2

Sample Input 2:
4
abab
2
bac
baba

Sample Output 2:
4

Sample Input 3:
6
abcabc
2
abca
cab

Sample Output 3:
1

----------------------------------------------------- SOLUTION -----------------------------------------------------

This problem can be solved by using a multiple substring search algorithm. The one used here is the Aho-Corasick
algorithm. It is slightly modified, so that instead of returning the occurences of each pattern, it returns a vector of
bool's that indicates whether a cell is tileable or not. These are filled up by finding an occurence of a pattern and
then setting all characters of the street to true for the length of that pattern.

One small optimization that was needed to improve the runtime was that when computing which words are contained in each
node of the trie, we only add all the ones from the suffix link if the node is not a word of the dictionary (patterns)
itself. This is because, all the words from the suffix link are strict suffixes of the word of the node (and we only
care about covering each cell once).

*/

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class TrieNode
{
  public:
    std::unordered_map<char, TrieNode *> children;
    TrieNode *suffix_link;
    std::vector<int> words;
    bool is_word = false;
};

TrieNode *build_aho_corasick_trie(const std::vector<std::string> &words)
{
    TrieNode *root = new TrieNode();

    // construct the trie with the normal down edges for all given words
    for (int i = 0; i < words.size(); i++)
    {
        TrieNode *current = root;
        for (int j = 0; j < words[i].size(); j++)
        {
            char letter = words[i][j];
            // child with letter doesn't exist
            if (current->children.find(letter) == current->children.end())
            {
                current->children[letter] = new TrieNode();
            }
            current = current->children[letter];
        }
        // this node portrays a word of the dictionary
        current->words.push_back(i);
        current->is_word = true;
    }

    // build suffix links (in case of failure) to the longest strict suffix of all nodes
    std::queue<TrieNode *> nodes;
    for (const std::pair<char, TrieNode *> child : root->children)
    {
        nodes.push(child.second);
        child.second->suffix_link = root;
    }

    while (!nodes.empty())
    {
        TrieNode *current = nodes.front();
        nodes.pop();

        for (const std::pair<char, TrieNode *> child : current->children)
        {
            TrieNode *suffix_link = current->suffix_link;
            while (suffix_link != NULL && suffix_link->children.find(child.first) == suffix_link->children.end())
            {
                suffix_link = suffix_link->suffix_link;
            }
            suffix_link = suffix_link == NULL ? root : suffix_link->children[child.first];
            child.second->suffix_link = suffix_link;
            // only add words of suffix link if it is not a word itself
            if (!child.second->is_word)
            {
                child.second->words.insert(child.second->words.begin(), suffix_link->words.begin(),
                                           suffix_link->words.end());
            }

            nodes.push(child.second);
        }
    }

    return root;
}

void delete_trie(TrieNode *root)
{
    for (const std::pair<char, TrieNode *> &child : root->children)
    {
        delete_trie(child.second);
    }
    delete root;
}

std::vector<bool> mark_tiles(const std::string &street, const std::vector<std::string> &words)
{
    TrieNode *root = build_aho_corasick_trie(words);
    TrieNode *current = root;
    std::vector<bool> tileable(street.size(), false);

    for (int i = 0; i < street.size(); i++)
    {
        // iterate suffix links until a node is found that has the current character as child
        while (current != NULL && current->children.find(street[i]) == current->children.end())
        {
            current = current->suffix_link;
        }
        if (current == NULL)
        {
            current = root;
            continue;
        }

        current = current->children[street[i]];
        // add all words of that node
        for (const int &word : current->words)
        {
            for (int j = i - words[word].size() + 1; j < i + 1; j++)
            {
                tileable[j] = true;
            }
        }
    }
    // make sure to delete all nodes of the trie
    delete_trie(root);

    return tileable;
}

int solve_problem(const std::pair<std::string, std::vector<std::string>> &problem)
{
    int untileable_cells = 0;

    std::vector<bool> tileable = mark_tiles(problem.first, problem.second);

    for (const bool &elem : tileable)
    {
        if (!elem)
        {
            untileable_cells++;
        }
    }
    return untileable_cells;
}