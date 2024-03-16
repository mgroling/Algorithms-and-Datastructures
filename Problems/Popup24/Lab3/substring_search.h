// Authors: Marc Gröling
// Methods for general use: kmp_search (algorithm for substring search)
// Helper methods: build_kmp_table

#ifndef substring_search
#define substring_search

#include <string>
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
std::vector<int> kmp_search(const std::string &text, const std::string &word)
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
            // character mismatch between word and text, check how far we need to go back using the kmp table
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

#endif