#pragma once

#include <vector>
#include <set>
#include <string>

/*!
 * \brief The Document struct Описание документа
 */
struct Document
{
    /*!
     * \brief id уникальный идентификатор документа
     */
    size_t id{0};

    /*!
     * \brief relevance релевантность документа
     */
    double relevance{0.};

    /*!
     * \brief rating рейтинг документа
     */
    int rating{0};
};

struct Query
{
    /*!
     * \brief words слова, включаемые в поиск
     */
    std::vector<std::string> words;

    /*!
     * \brief noWords слова, исключаемые из поиска
     */
    std::set<std::string> excludedWords;

    /*!
     * \brief idf inverse document frequency или полезность слова. Чем в большем количестве документов есть слово, тем ниже его IDF
     */
    std::vector<double> idf;
};
