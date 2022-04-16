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

        /*!
         * \brief TransformStringToCase Трансформация строки в нужный регистр
         * \param str строка
         * \return трансформированная строка
         */
        NO_DISCARD static std::string TransformStringToCase(std::string str, bool lower);

        /*!
         * \brief LexicographicalSorting Лексикографическая сортировка
         * \param vec сортируемый массив
         */
        static void LexicographicalSorting(std::vector<std::string>& vec);

        /*!
         * \brief ContainWordCount Подсчёт количества данных, содержащее искомое слово
         * \param data данные
         * \param word слово
         * \return количество
         */
        NO_DISCARD static size_t ContainWordCount(const std::vector<std::string>& data, const std::string& word);
    };
}
