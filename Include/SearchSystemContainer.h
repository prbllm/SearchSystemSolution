#pragma once

#include <set>
#include <string>

// Self
#include <Def.h>

/*!
 * \brief The SearchSystemContainer class Контейнер для поисковой системы
 */
class SearchSystemContainer final
{
public:
    /*!
     * \brief SearchSystemContainer Конструктор
     */
    explicit SearchSystemContainer();

    /*!
     * \brief SearchSystemContainer Деструктор по умолчанию
     */
    ~SearchSystemContainer();

    /*!
     * \brief GetStopWords Получение запрещённых слов
     * \return запрещённые слова
     */
    NO_DISCARD const std::set<std::string>& GetStopWords() const;

    /*!
     * \brief InitializeStopWords Инициализация запрещённых слов
     * \param words запрещённые слова
     */
    void InitializeStopWords(const std::set<std::string>& words);

    /*!
     * \brief InitializeStopWords Инициализация запрещённых слов
     * \param words запрещённые слова
     */
    void InitializeStopWords(const std::string& words);

    /*!
     * \brief InitializeStopWords Инициализация запрещённых слов
     * \param words запрещённые слова
     */
    void InitializeStopWords(std::set<std::string>&& words);

private:
    /*!
     * \brief _stopWords Запрещённые слова
     */
    std::set<std::string> _stopWords;
};
