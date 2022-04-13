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
        return res;
    }

}
