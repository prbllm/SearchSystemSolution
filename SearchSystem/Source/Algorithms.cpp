#include "Algorithms.h"

#include <iostream>
#include <algorithm>
#include <vector>

namespace Algorithms
{
    std::string Algorithms::ReadLine()
    {
        std::string res;
        std::getline(std::cin, res);
        return res;
    }

    int Algorithms::ReadLineWithNumber()
    {
        int res{0};
        std::cin >> res;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return res;
    }

    std::vector<std::string> Algorithms::SplitIntoWords(const std::string &text)
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

    int Algorithms::CountStartsWith(const std::vector<std::string> &xs, char sym)
    {
        return std::count_if(xs.begin(), xs.end(), [&sym = std::as_const(sym)](const std::string& word)
        {
            return word.front() == sym;
        });
    }

    std::pair<bool, double> Algorithms::CalculateMedian(const std::vector<double>& samples)
    {
        if (samples.empty())
            return std::make_pair(false, 0);

        auto vec = samples;
        std::sort(vec.begin(), vec.end());
        if (vec.size() % 2)
            return std::make_pair(true, vec[static_cast<int>((vec.size() - 1) / 2)]);

        auto pos = static_cast<int>(vec.size() / 2);
        return std::make_pair(true, (vec[pos - 1] + vec[pos]) / 2);
    }
}
