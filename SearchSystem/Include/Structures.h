#pragma once

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
    size_t relevance{0};
};

struct Query
{
    /*!
     * \brief words слова, включаемые в поиск
     */
    std::set<std::string> words;

    /*!
     * \brief noWords слова, исключаемые из поиска
     */
    std::set<std::string> excludedWords;
};
