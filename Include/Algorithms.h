#pragma once

#include <string>
#include <vector>

namespace Algorithms
{
    /*!
     * \brief The Algorthms class Алгоритмы
     */
    class Algorthms final
    {
    public:
        /*!
         * \brief ReadLine Чтение строки из консоли
         * \return строка
         */
        static std::string ReadLine();

        /*!
         * \brief ReadLineWithNumber Чтение числа из консоли
         * \return число
         */
        static int ReadLineWithNumber();

        /*!
         * \brief SplitIntoWords Разбор строки по словам
         * \param text строка
         * \return слова
         */
        static std::vector<std::string> SplitIntoWords(const std::string& text);
    };
}
