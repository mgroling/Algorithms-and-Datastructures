// Authors: Marc Gröling
// Methods for general use: substring_search (algorithm for substring search, one for one pattern and one for multiple
// patterns, functions are overloaded)
// Helper methods: build_kmp_table, build_aho_corasick_trie (with TrieNode)

#ifndef substring_search_h
#define substring_search_h

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

// builds the table for kmp backtracking
std::vector<int> build_kmp_table(const std::string &word)
{
    // kmp_table[i] = there is a match from word[0] to word[i - 1] in the text, but text[j] != word[i], at what position
    // could word appear again?
    std::vector<int> kmp_table(word.size() + 1);
    int pos = 1;
    int candidate = 0;

    kmp_table[0] = -1;
    while (pos < word.size())
    {
        if (word[pos] == word[candidate])
        {
            kmp_table[pos] = kmp_table[candidate];
        }
        else
        {
            kmp_table[pos] = candidate;
            while (candidate >= 0 && word[pos] != word[candidate])
            {
                candidate = kmp_table[candidate];
            }
        }
        pos++;
        candidate++;
    }

    kmp_table[pos] = candidate;

    return kmp_table;
}

// finds all occurences of word in text and returns the index of them (where occurences start)
// uses the Knuth–Morris–Pratt algorithm internally with O(|text| + |word|) time complexity
std::vector<int> substring_search(const std::string &text, const std::string &word)
{
    std::vector<int> word_positions;

    int text_pos = 0;
    int word_pos = 0;
    std::vector<int> kmp_table = build_kmp_table(word);

    while (text_pos < text.size())
    {
        if (word[word_pos] == text[text_pos])
        {
            text_pos++;
            word_pos++;
            // occurence of word found, check kmp table for how far we need to go back in the word for the next
            // occurence
            if (word_pos == word.size())
            {
                word_positions.push_back(text_pos - word_pos);
                word_pos = kmp_table[word_pos];
            }
        }
        else
        {
            // letter mismatch between word and text, check how far we need to go back using the kmp table
            word_pos = kmp_table[word_pos];
            if (word_pos == -1)
            {
                word_pos++;
                text_pos++;
            }
        }
    }

    return word_positions;
}

class TrieNode
{
  public:
    std::unordered_map<char, TrieNode *> children;
    TrieNode *suffix_link;
    std::vector<int> words;
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
            // add all words that are suffixes to this node for the substring search later
            child.second->words.insert(child.second->words.begin(), suffix_link->words.begin(),
                                       suffix_link->words.end());
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

// returns the array of occurences for each word (it starts at that index)
std::vector<std::vector<int>> substring_search(const std::string &text, const std::vector<std::string> &words)
{
    TrieNode *root = build_aho_corasick_trie(words);
    TrieNode *current = root;
    std::vector<std::vector<int>> word_positions(words.size(), std::vector<int>{});

    for (int i = 0; i < text.size(); i++)
    {
        // iterate suffix links until a node is found that has the current character as child
        while (current != NULL && current->children.find(text[i]) == current->children.end())
        {
            current = current->suffix_link;
        }
        if (current == NULL)
        {
            current = root;
            continue;
        }

        current = current->children[text[i]];
        // add all words of that node
        for (const int &word : current->words)
        {
            word_positions[word].push_back(i - words[word].size() + 1);
        }
    }
    // make sure to delete all nodes of the trie
    delete_trie(root);

    return word_positions;
}

#endif