#pragma once

// Self
#include "Def.h"

#include <string>
#include <vector>

namespace Algorithms
{
    /*!
     * \brief The Algorthms class Алгоритмы
     */
    class Algorithms final
    {
    public:
        /*!
         * \brief ReadLine Чтение строки из консоли
         * \return строка
         */
        NO_DISCARD static std::string ReadLine();

        /*!
         * \brief ReadLineWithNumber Чтение числа из консоли
         * \return число
         */
        NO_DISCARD static int ReadLineWithNumber();

        /*!
         * \brief SplitIntoWords Разбор строки по словам
         * \param text строка
         * \return слова
         */
        NO_DISCARD static std::vector<std::string> SplitIntoWords(const std::string& text);

        /*!
         * \brief CountStartsWith Числов слов, начинающихся на заданный символ
         * \param xs строки
         * \param sym символ
         * \return количество строк
         */
        NO_DISCARD static int CountStartsWith(const std::vector<std::string>& xs, char sym);

        /*!
         * \brief CalculateMedian Рассчёт медианы отрезка
         * \param samples отрезок значений
         * \return медиана (true - если есть)
         */
        NO_DISCARD static std::pair<bool, double> CalculateMedian(const std::vector<double>& samples);
    };
}
