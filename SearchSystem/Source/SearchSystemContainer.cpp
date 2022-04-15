#include "SearchSystemContainer.h"

// Self
#include "Algorithms.h"

#include <algorithm>
#include <execution>

struct SearchSystemContainer::Data
{
    /*!
     * \brief Data Конструктор по умолчанию
     */
    explicit Data() = default;

    /*!
     * \brief stopWords Запрещённые слова
     */
    std::set<std::string> stopWords;

    /*!
     * \brief documents Документы
     */
    std::vector<std::pair<size_t, std::vector<std::string>>> documents;
};

SearchSystemContainer::SearchSystemContainer()
    : _data(std::make_unique<Data>())
{
    _data->stopWords = std::set<std::string>{"a", "an", "on", "the", "in", "is", "has", "been", "are", "with", "for", "from", "have", "be", "was"};

    _data->documents.reserve(4);
    _data->documents.emplace_back(
                std::make_pair(
                0, std::vector<std::string>{"small", "curly", "guinea", "pig", "grey", "hair", "found"}
                ));
    _data->documents.emplace_back(
                std::make_pair(
                1, std::vector<std::string>{"young", "50", "year", "old", "crocodile", "wants", "to", "make", "friends"}
                ));
    _data->documents.emplace_back(
                std::make_pair(
                2, std::vector<std::string>{"strange", "brown", "creature", "seen", "box", "of", "oranges"}
                ));
    _data->documents.emplace_back(
                std::make_pair(
                3, std::vector<std::string>{"strange", "animal", "big", "ears", "building", "house", "its", "friends"}
                ));
}

SearchSystemContainer::~SearchSystemContainer() = default;

const std::set<std::string> &SearchSystemContainer::GetStopWords() const
{
    return _data->stopWords;
}

void SearchSystemContainer::InitializeStopWords(const std::set<std::string>& words)
{
    _data->stopWords = words;
}

void SearchSystemContainer::InitializeStopWords(const std::string &words)
{
    if (words.empty())
        return;

    const auto& parsing = Algorithms::Algorithms::SplitIntoWords(words);
    _data->stopWords = std::set<std::string>{parsing.begin(), parsing.end()};
}

void SearchSystemContainer::InitializeStopWords(std::set<std::string> &&words)
{
    _data->stopWords = words;
}

const SearchSystemContainer::Documents &SearchSystemContainer::GetDocuments() const
{
    return _data->documents;
}

void SearchSystemContainer::InitializeDocuments(const Documents &docs)
{
    _data->documents = docs;
}

void SearchSystemContainer::InitializeDocuments(Documents &&docs)
{
    _data->documents = docs;
}

void SearchSystemContainer::AddDocument(const std::vector<std::string> &doc)
{
    auto res = doc;
    CheckStopWords(res);
    _data->documents.push_back(std::make_pair(_data->documents.size(), std::move(res)));
}

void SearchSystemContainer::ClearDocuments()
{
    _data->documents.clear();
}

std::vector<Document> SearchSystemContainer::FindDocuments(const std::string &query)
{
    return FindDocuments(Algorithms::Algorithms::SplitIntoWords(query));
}

std::vector<Document> SearchSystemContainer::FindDocuments(const std::vector<std::string> &query)
{
    auto resultQuery = query;
    CheckStopWords(resultQuery);
    auto queryUnique = std::set<std::string>{resultQuery.begin(), resultQuery.end()};

    std::vector<Document> result;
    result.reserve(_data->documents.size());

    for (const auto& doc : _data->documents)
        result.emplace_back(Document{doc.first, MatchDocument(doc, queryUnique)});
    return result;
}

std::vector<Document> SearchSystemContainer::FindTopDocuments(const std::vector<std::string> &query, size_t count)
{
    auto res = FindDocuments(query);
    std::sort(std::execution::par, res.begin(), res.end(),[](const Document &a, const Document &b)
    {
        return a.relevance > b.relevance;
    });

    if (count < res.size())
        return std::vector<Document>{res.begin(), res.begin() + count};
    return res;
}

void SearchSystemContainer::CheckStopWords(std::vector<std::string> &words)
{
    words.erase(std::remove_if(words.begin(), words.end(), [this](const std::string& word)
    {
        return _data->stopWords.count(word);
    }), words.end());
}

size_t SearchSystemContainer::MatchDocument(const std::pair<int, std::vector<std::string> > &doc, const std::set<std::string> &queryUnique)
{
    return std::count_if(queryUnique.begin(), queryUnique.end(), [&doc = std::as_const(doc)](const std::string& word)
    {
        auto it = std::find(doc.second.begin(), doc.second.end(), word);
        if (it != doc.second.end())
            return true;
        return false;
    });
}
