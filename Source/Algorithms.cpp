#include "Algorithms.h"

#include <iostream>

namespace Algorithms
{
    std::string Algorthms::ReadLine()
    {
        std::string res;
        std::getline(std::cin, res);
        return res;
    }

    int Algorthms::ReadLineWithNumber()
    {
        int res{0};
        std::cin >> res;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return res;
    }

    std::vector<std::string> Algorthms::SplitIntoWords(const std::string &text)
    {
        std::vector<std::string> words;
        std::string word;
        for (const char c : text)
        {
            if (c == ' ')
            {
                if (!word.empty())
                {
                    words.push_back(word);
                    word.clear();
                }
            }
            else
            {
                word += c;
            }
        }
        if (!word.empty())
            words.push_back(word);

        return words;
    }
}
