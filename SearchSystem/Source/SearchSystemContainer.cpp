#include "SearchSystemContainer.h"

// Self
#include "Algorithms.h"

#include <algorithm>
#include <cmath>
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

std::vector<Document> SearchSystemContainer::FindDocuments(const std::string &query) const
{
    return FindDocuments(Algorithms::Algorithms::SplitIntoWords(query));
}

std::vector<Document> SearchSystemContainer::FindDocuments(const std::vector<std::string> &query, bool all) const
{
    auto resultQuery = ParseQuery(query);

    std::vector<Document> result;
    result.reserve(_data->documents.size());

    for (const auto& doc : _data->documents)
    {
        auto rel = MatchDocument(doc, resultQuery);
        if (all)
        {
            result.emplace_back(Document{doc.first, rel});
            continue;
        }

        if (!rel)
            continue;

        auto it = std::find_if(doc.second.begin(), doc.second.end(),
                               [&words = std::as_const(resultQuery.excludedWords)](const std::string& word)
        {
            return words.count(word);
        });
        if (it != doc.second.end())
            continue;
        result.emplace_back(Document{doc.first, rel});
    }
    return result;
}

std::vector<Document> SearchSystemContainer::FindTopDocuments(const std::vector<std::string> &query, size_t count)
{
    auto res = FindDocuments(query, true);
    std::sort(std::execution::par, res.begin(), res.end(),[](const Document &a, const Document &b)
    {
        return a.relevance > b.relevance;
    });

    if (count < res.size())
        return std::vector<Document>{res.begin(), res.begin() + count};
    return res;
}

void SearchSystemContainer::CheckStopWords(std::vector<std::string> &words) const
{
    words.erase(std::remove_if(words.begin(), words.end(), [this](const std::string& word)
    {
        return _data->stopWords.count(word);
    }), words.end());
}

std::set<std::string> SearchSystemContainer::CreateUniqueWords(const std::vector<std::string> &words) const
{
    std::set<std::string> res;
    std::copy_if(words.begin(), words.end(), std::inserter(res, res.begin()), [this](const std::string& word)
    {
        return !_data->stopWords.count(word);
    });
    return res;
}

double SearchSystemContainer::MatchDocument(const std::pair<int, std::vector<std::string> > &doc, const Query& queryUnique) const
{
    // релевантоность документа рассчитаем по формуле - суммируем значение tf * idf для каждого слова в запросе
    // tf - term frequency - доля слова в документе (сколько данное слово встречается в документе делённое на общее количество слов)
    if (queryUnique.words.size() != queryUnique.idf.size())
        return 0.;

    double sum{0.};
    for (size_t i{0}; i < queryUnique.words.size(); ++i)
    {
        auto count = std::count(std::execution::par, doc.second.begin(), doc.second.end(), queryUnique.words[i]);
        sum += static_cast<double>(count) / static_cast<double>(doc.second.size()) * queryUnique.idf[i];
    }

    return sum;
}

Query SearchSystemContainer::ParseQuery(std::vector<std::string> query) const
{
    Query res;

    auto it = std::remove_if(std::execution::par, query.begin(), query.end(), [](const std::string& word)
    {
        if (!word.empty())
            return word.front() == '-';
        return false;
    });

    res.words = std::vector<std::string>{query.begin(), it};
    CheckStopWords(res.words);

    res.idf.reserve(res.words.size());
    for (const auto& word : res.words)
    {
        // рассчитываем idf по формуле - натуральный логарифм от количества документов делённых на количество докуметов, где встречается слово
        auto count = std::count_if(std::execution::par, _data->documents.begin(), _data->documents.end(),
                                   [&word = std::as_const(word)](const std::pair<int, std::vector<std::string>>& doc)
        {
            auto it = std::find(std::execution::par, doc.second.begin(), doc.second.end(), word);
            if (it != doc.second.end())
                return true;
            return false;
        });
        if (!count)
        {
            res.idf.emplace_back(0.);
            continue;
        }
        res.idf.emplace_back(std::log(static_cast<double>(_data->documents.size()) / static_cast<double>(count)));
    }

    auto temp = std::vector<std::string>{it, query.end()};
    std::transform(std::execution::par, temp.begin(), temp.end(), temp.begin(),[](const std::string& word)
    {
       return word.substr(1);
    });

    res.excludedWords = CreateUniqueWords(temp);

    return res;
}
