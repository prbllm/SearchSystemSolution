#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../../SearchSystem/Include/SearchSystemContainer.h"

using namespace testing;

/*!
 * \brief The SearchSystemContainerTest class класс для тестирования контейнера поисковой системы
 */
class SearchSystemContainerTest : public Test
{
protected:

    /*!
     * \brief SearchSystemContainerTest Конструктор
     */
    explicit SearchSystemContainerTest()
    {
        _container = std::make_unique<SearchSystemContainer>();
    };

    /*!
     * \brief ~SearchSystemContainerTest Деструктор по умолчанию
     */
    ~SearchSystemContainerTest() = default;

    /*!
     * \brief SetUp Переопределяемая фукция установки первоначальных значений
     */
    void SetUp() override
    {
    };

    /*!
     * \brief TearDown Переопределяемая функция очищения значений
     */
    void TearDown() override
    {
    };

    /*!
     * \brief _container Тестируемый класс
     */
    std::unique_ptr<SearchSystemContainer> _container;
};

TEST_F(SearchSystemContainerTest, SearchSystemContainerDefaultTest)
{
    EXPECT_EQ(_container->GetStopWords()
              , (std::set<std::string>{"a", "an", "on", "the", "in", "is", "has", "been", "are", "with", "for", "from", "have", "be", "was"}));

    ASSERT_EQ(_container->GetDocuments().size(), static_cast<size_t>(4));
    std::vector<std::pair<size_t, std::vector<std::string>>> documents;
    documents.emplace_back(
                std::make_pair(
                0, std::vector<std::string>{"small", "curly", "guinea", "pig", "grey", "hair", "found"}
                ));
    documents.emplace_back(
                std::make_pair(
                1, std::vector<std::string>{"young", "50", "year", "old", "crocodile", "wants", "to", "make", "friends"}
                ));
    documents.emplace_back(
                std::make_pair(
                2, std::vector<std::string>{"strange", "brown", "creature", "seen", "box", "of", "oranges"}
                ));
    documents.emplace_back(
                std::make_pair(
                3, std::vector<std::string>{"strange", "animal", "big", "ears", "building", "house", "its", "friends"}
                ));

    const auto& docs = _container->GetDocuments();
    for (size_t i{0}; i < docs.size(); ++i)
        EXPECT_EQ(docs[i], documents[i]) << "Documents are not equal at position " << i;
}

TEST_F(SearchSystemContainerTest, SearchSystemContainerInitializeStopWordsTest)
{
    auto res = std::set<std::string>{"a", "b", "c"};
    _container->InitializeStopWords(res);

    EXPECT_EQ(_container->GetStopWords(), res);

    _container->InitializeStopWords("c a b a");
    EXPECT_EQ(_container->GetStopWords(), (std::set<std::string>{"c", "b", "a"}));

    _container->InitializeStopWords(std::move(res));
    EXPECT_EQ(_container->GetStopWords(), (std::set<std::string>{"a", "b", "c"}));
}

TEST_F(SearchSystemContainerTest, SearchSystemContainerInitializeDocumentsTest)
{
    std::vector<std::pair<size_t, std::vector<std::string>>> res;
    res.emplace_back(std::make_pair(0, std::vector<std::string>{"lets", "party", "started"}));

    _container->InitializeDocuments(res);
    EXPECT_EQ(_container->GetDocuments(), res);

    _container->ClearDocuments();
    EXPECT_EQ(_container->GetDocuments(), (std::vector<std::pair<size_t, std::vector<std::string>>>()));

    res.emplace_back(std::make_pair(1, std::vector<std::string>{"eee", "lets", "rock"}));
    auto temp = res;
    _container->InitializeDocuments(std::move(temp));
    EXPECT_EQ(_container->GetDocuments(), res);

     res.emplace_back(std::make_pair(2, std::vector<std::string>{"already", "started!"}));
    _container->AddDocument(std::vector<std::string>{"already", "started!"});
    EXPECT_EQ(_container->GetDocuments(), res);
}

TEST_F(SearchSystemContainerTest, SearchSystemContainerFindDocumentsTest)
{
    auto query = std::vector<std::string>{"cheburashka", "with", "big", "ears", "likes", "oranges"};

    std::vector<Document> resultFull{Document{0, 0}, Document{1, 0}, Document{2, 1}, Document{3, 2}};
    std::vector<Document> result{Document{2, 1}, Document{3, 2}};

    auto resF = _container->FindDocuments(query);
    ASSERT_EQ(result.size(), resF.size());

    for (size_t i{0}; i < resF.size(); ++i)
    {
        EXPECT_EQ(result[i].id, resF[i].id);
        EXPECT_EQ(result[i].relevance, resF[i].relevance);
    }

    resF = _container->FindDocuments("cheburashka with big ears likes oranges");
    ASSERT_EQ(result.size(), resF.size());

    for (size_t i{0}; i < resF.size(); ++i)
    {
        EXPECT_EQ(result[i].id, resF[i].id);
        EXPECT_EQ(result[i].relevance, resF[i].relevance);
    }

    resF = _container->FindDocuments(query, true);
    ASSERT_EQ(resultFull.size(), resF.size());

    for (size_t i{0}; i < resF.size(); ++i)
    {
        EXPECT_EQ(resultFull[i].id, resF[i].id);
        EXPECT_EQ(resultFull[i].relevance, resF[i].relevance);
    }
}

TEST_F(SearchSystemContainerTest, SearchSystemContainerFindTopDocumentsTest)
{
    std::vector<Document> result{Document{3, 2}, Document{2, 1}, Document{0, 0}, Document{1, 0}};
    auto query = std::vector<std::string>{"cheburashka", "with", "big", "ears", "likes", "oranges"};

    auto resF = _container->FindTopDocuments(query, 0);
    ASSERT_EQ(0, resF.size());

    resF = _container->FindTopDocuments(query, 3);
    ASSERT_EQ(3, resF.size());

    for (size_t i{0}; i < resF.size(); ++i)
    {
        EXPECT_EQ(result[i].relevance, resF[i].relevance);
    }
}

TEST_F(SearchSystemContainerTest, SearchSystemContainerFindTopDocumentsWithMinusWordsTest)
{
    _container->InitializeStopWords(std::set<std::string>{"и", "в", "на"});
    _container->ClearDocuments();
    _container->AddDocument(std::vector<std::string>{"белый", "кот", "и", "модный", "ошейник"});
    _container->AddDocument(std::vector<std::string>{"пушистый", "кот", "пушистый", "хвост"});
    _container->AddDocument(std::vector<std::string>{"ухоженный", "пёс", "выразительные", "глаза"});

    auto resF = _container->FindDocuments(std::vector<std::string>{"пушистый", "ухоженный", "кот", "-ошейник"});
    std::vector<Document> result{Document{1, 2}, Document{2, 1}};

    ASSERT_EQ(result.size(), resF.size());

    for (size_t i{0}; i < resF.size(); ++i)
    {
        EXPECT_EQ(result[i].id, resF[i].id);
        EXPECT_EQ(result[i].relevance, resF[i].relevance);
    }
}