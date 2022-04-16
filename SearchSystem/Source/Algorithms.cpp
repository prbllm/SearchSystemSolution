#include "Algorithms.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <execution>

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
        std::sort(std::execution::par, vec.begin(), vec.end());
        if (vec.size() % 2)
            return std::make_pair(true, vec[static_cast<int>((vec.size() - 1) / 2)]);

        auto pos = static_cast<int>(vec.size() / 2);
        return std::make_pair(true, (vec[pos - 1] + vec[pos]) / 2);
    }

    std::string Algorithms::TransformStringToCase(std::string str, bool lower)
    {
        std::transform(std::execution::par, str.begin(), str.end(), str.begin(), [&lower = std::as_const(lower)](unsigned char c)
        {
            return lower ? std::tolower(c) : std::toupper(c);
        });
        return str;
    }

    void Algorithms::LexicographicalSorting(std::vector<std::string> &vec)
    {
        if (vec.empty())
            return;

        std::sort(vec.begin(), vec.end(), [](const std::string& a, const std::string& b)
        {
            return TransformStringToCase(a, true) < TransformStringToCase(b, true);
        });
    }
}
