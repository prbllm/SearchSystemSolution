#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

// Self
#include <Def.h>
#include "Structures.h"

/*!
 * \brief The SearchSystemContainer class Контейнер для поисковой системы
 */
class SearchSystemContainer final
{
    using Documents = std::vector<std::pair<size_t, std::vector<std::string>>>;
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

    /*!
     * \brief GetDocuments Получение документов
     * \return документы
     */
    NO_DISCARD const Documents& GetDocuments() const;

    /*!
     * \brief InitializeDocuments Инициализация документов
     * \param docs документы
     */
    void InitializeDocuments(const Documents& docs);

    /*!
     * \brief InitializeDocuments Инициализация документов
     * \param docs документы
     */
    void InitializeDocuments(Documents&& docs);

    /*!
     * \brief AddDocument Добавление документа
     * \param docs документы
     * \param status статус документа
     * \param marks оценки
     */
    void AddDocument(const std::vector<std::string>& doc, DocumentStatus status, const std::vector<int>& marks);

    /*!
     * \brief ClearDocuments Очищение документов
     */
    void ClearDocuments();

    /*!
     * \brief FindDocuments Поиск документов
     * \param query поисковая строка
     * \param status статус документов, по которым ищем
     * \return результат поиска в формате уникальный идентификатор документа - релевантность
     */
    NO_DISCARD std::vector<Document> FindDocuments(const std::string& query, DocumentStatus status) const;

    /*!
     * \brief FindDocuments Поиск документов
     * \param query поисковая строка
     * \param status статус документов, по которым ищем
     * \param all все документы
     * \return результат поиска в формате уникальный идентификатор документа - релевантность
     */
    NO_DISCARD std::vector<Document> FindDocuments(const std::vector<std::string>& query, DocumentStatus status, bool all = false) const;

    /*!
     * \brief FindTopDocuments Поиск документов с высокой релевантностью
     * \param query запрос
     * \param status статус документов, по которым ищем
     * \param count количество документов
     * \return результат поиска в формате уникальный идентификатор документа - релевантность
     */
    NO_DISCARD std::vector<Document> FindTopDocuments(const std::vector<std::string>& query, DocumentStatus status = DocumentStatus::ACTUAL, size_t count = 5);

    /*!
     * \brief FindTopDocuments Поиск документов с высокой релевантностью
     * \param query запрос
     * \param status статус документов, по которым ищем
     * \param count количество документов
     * \return результат поиска в формате уникальный идентификатор документа - релевантность
     */
    NO_DISCARD std::vector<Document> FindTopDocuments(const std::string& query, DocumentStatus status = DocumentStatus::ACTUAL, size_t count = 5);

private:

    /*!
     * \brief Данные
     */
    struct Data;

    /*!
     * \brief _data Данные
     */
    std::unique_ptr<Data> _data;

    /*!
     * \brief CheckStopWords Изменение слов с учётом запрещённых
     * \param words слова
     */
    void CheckStopWords(std::vector<std::string>& words) const;

    /*!
     * \brief CreateUniqueWords Создание уникальных слов
     * \param words изначальный массив слов
     * \return уникальный массив слов
     */
    std::set<std::string> CreateUniqueWords(const std::vector<std::string>& words) const;

    /*!
     * \brief MatchDocuments Определение релевантности документа
     * \param doc документ
     * \param query слова запроса
     * \return релевантность
     */
    NO_DISCARD double MatchDocument(const std::pair<int, std::vector<std::string>>& doc, const Query& query) const;

    /*!
     * \brief ParseQuery Разбор запроса
     * \param query запрос
     * \return запрос
     */
    NO_DISCARD Query ParseQuery(std::vector<std::string> query) const;
};
