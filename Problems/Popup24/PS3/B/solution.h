#include <cmath>
#include <string>
#include <vector>

std::vector<std::string> solve_problem(const Test_case &test_case)
{
    unsigned long long count_all_permutations = 1;
    for (const std::pair<std::string, int> word : test_case.word_repetitions)
    {
        count_all_permutations *= std::pow((unsigned long long)test_case.all_translations.at(word.first).first,
                                           (unsigned long long)word.second);
    }

    if (count_all_permutations == 1)
    {
        std::string sentence;
        bool correct = true;
        for (const std::string &word : test_case.sentence)
        {
            sentence += test_case.all_translations.at(word).second + ' ';
            auto ptr = test_case.correct_translations.find(word);
            if (ptr == test_case.correct_translations.end())
            {
                correct = false;
            }
        }

        return {sentence, correct ? "correct" : "incorrect"};
    }

    unsigned long long count_correct_permutations = 1;
    for (const std::pair<std::string, int> word : test_case.word_repetitions)
    {
        auto ptr = test_case.correct_translations.find(word.first);
        if (ptr == test_case.correct_translations.end())
        {
            return {"0 correct", std::to_string(count_all_permutations) + " incorrect"};
        }
        count_correct_permutations *= std::pow((unsigned long long)ptr->second.first, (unsigned long long)word.second);
    }

    return {std::to_string(count_correct_permutations) + " correct",
            std::to_string(count_all_permutations - count_correct_permutations) + " incorrect"};
}