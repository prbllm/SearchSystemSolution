#pragma once

#include <string>

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
    };
}
