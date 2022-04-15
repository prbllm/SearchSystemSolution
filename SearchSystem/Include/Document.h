#pragma once

#include <cstdlib>

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
