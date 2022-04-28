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
     _container->AddDocument(std::vector<std::string>{"already", "started!"}, DocumentStatus::ACTUAL, std::vector<int>{});
    EXPECT_EQ(_container->GetDocuments(), res);
}

TEST_F(SearchSystemContainerTest, SearchSystemContainerFindDocumentsTest)
{
    auto query = std::vector<std::string>{"cheburashka", "with", "big", "ears", "likes", "oranges"};

    std::vector<Document> resultFull{Document{0, 0.}, Document{1, 0.}, Document{2, 0.198042}, Document{3, 0.346574}};
    std::vector<Document> result{Document{2, 0.198042051}, Document{3, 0.346574}};

    auto resF = _container->FindDocuments(query, DocumentStatus::ACTUAL);
    ASSERT_EQ(result.size(), resF.size());

    for (size_t i{0}; i < resF.size(); ++i)
    {
        EXPECT_EQ(result[i].id, resF[i].id);
        EXPECT_NEAR(result[i].relevance, resF[i].relevance, 0.0001);
    }

    resF = _container->FindDocuments("cheburashka with big ears likes oranges", DocumentStatus::ACTUAL);
    ASSERT_EQ(result.size(), resF.size());

    for (size_t i{0}; i < resF.size(); ++i)
    {
        EXPECT_EQ(result[i].id, resF[i].id);
        EXPECT_NEAR(result[i].relevance, resF[i].relevance, 0.0001);
    }

    resF = _container->FindDocuments(query, DocumentStatus::ACTUAL, true);
    ASSERT_EQ(resultFull.size(), resF.size());

    for (size_t i{0}; i < resF.size(); ++i)
    {
        EXPECT_EQ(resultFull[i].id, resF[i].id);
        EXPECT_NEAR(resultFull[i].relevance, resF[i].relevance, 0.0001);
    }
}

TEST_F(SearchSystemContainerTest, SearchSystemContainerFindTopDocumentsTest)
{
    std::vector<Document> result{Document{3, 0.346574}, Document{2, 0.198042}, Document{0, 0.}, Document{1, 0.}};
    auto query = std::vector<std::string>{"cheburashka", "with", "big", "ears", "likes", "oranges"};

    auto resF = _container->FindTopDocuments(query, DocumentStatus::ACTUAL, 0);
    ASSERT_EQ(0, resF.size());

    resF = _container->FindTopDocuments(query, DocumentStatus::ACTUAL, 3);
    ASSERT_EQ(3, resF.size());

    for (size_t i{0}; i < resF.size(); ++i)
        EXPECT_NEAR(result[i].relevance, resF[i].relevance, 0.0001);
}

TEST_F(SearchSystemContainerTest, SearchSystemContainerFindTopDocumentsStatusTest)
{
    _container->InitializeStopWords(std::set<std::string>{"и", "в", "на"});
    _container->ClearDocuments();
    _container->AddDocument(std::vector<std::string>{"белый", "кот", "и", "модный", "ошейник"}, DocumentStatus::ACTUAL, std::vector<int>{8, -3});
    _container->AddDocument(std::vector<std::string>{"пушистый", "кот", "пушистый", "хвост"}, DocumentStatus::ACTUAL, std::vector<int>{7, 2, 7});
    _container->AddDocument(std::vector<std::string>{"ухоженный", "пёс", "выразительные", "глаза"}, DocumentStatus::ACTUAL, std::vector<int>{5, -12, 2, 1});
    _container->AddDocument(std::vector<std::string>{"ухоженный", "скворец", "евгений"}, DocumentStatus::BANNED, std::vector<int>{9});

     std::vector<Document> result1{
         Document{1, 0.866434, 5, DocumentStatus::ACTUAL}
         , Document{0, 0.173287, 3, DocumentStatus::ACTUAL}
         , Document{2, 0.173287, -1, DocumentStatus::ACTUAL}};
     std::vector<Document> result2{Document{3, 0.231049, 9, DocumentStatus::BANNED}};

    auto res = _container->FindTopDocuments("пушистый ухоженный кот");
    ASSERT_EQ(3, res.size());

    for (size_t i{0}; i < res.size(); ++i)
    {
        EXPECT_EQ(res[i].id, result1[i].id);
        EXPECT_NEAR(res[i].relevance, result1[i].relevance, 0.0001);
        EXPECT_EQ(res[i].rating, result1[i].rating);
        EXPECT_EQ(res[i].status, result1[i].status);
    }

    res = _container->FindTopDocuments("пушистый ухоженный кот", DocumentStatus::BANNED);
    ASSERT_EQ(1, res.size());

    EXPECT_EQ(res[0].id, result2[0].id);
    EXPECT_NEAR(res[0].relevance, result2[0].relevance, 0.0001);
    EXPECT_EQ(res[0].rating, result2[0].rating);
    EXPECT_EQ(res[0].status, result2[0].status);
}

TEST_F(SearchSystemContainerTest, SearchSystemContainerFindDocumentsWithMinusWordsTest)
{
    _container->InitializeStopWords(std::set<std::string>{"и", "в", "на"});
    _container->ClearDocuments();
    _container->AddDocument(std::vector<std::string>{"белый", "кот", "и", "модный", "ошейник"}, DocumentStatus::ACTUAL, std::vector<int>{2, 8, -3});
    _container->AddDocument(std::vector<std::string>{"пушистый", "кот", "пушистый", "хвост"}, DocumentStatus::ACTUAL, std::vector<int>{3, 7, 2, 7});
    _container->AddDocument(std::vector<std::string>{"ухоженный", "пёс", "выразительные", "глаза"}, DocumentStatus::ACTUAL, std::vector<int>{4, 5, -12, 2, 1});

    auto resF = _container->FindDocuments(std::vector<std::string>{"пушистый", "ухоженный", "кот", "-ошейник"}, DocumentStatus::ACTUAL);
    std::vector<Document> result{Document{1, 0.650672}, Document{2, 0.274653}};

    ASSERT_EQ(result.size(), resF.size());

    for (size_t i{0}; i < resF.size(); ++i)
    {
        EXPECT_EQ(result[i].id, resF[i].id);
        EXPECT_NEAR(result[i].relevance, resF[i].relevance, 0.0001);
    }
}

TEST_F(SearchSystemContainerTest, SearchSystemContainerFindDocumentsRatingTest)
{
    _container->InitializeStopWords(std::set<std::string>{"и", "в", "на"});
    _container->ClearDocuments();
    _container->AddDocument(std::vector<std::string>{"белый", "кот", "и", "модный", "ошейник"}, DocumentStatus::ACTUAL, std::vector<int>{2, 8, -3});
    _container->AddDocument(std::vector<std::string>{"пушистый", "кот", "пушистый", "хвост"}, DocumentStatus::ACTUAL, std::vector<int>{3, 7, 2, 7});
    _container->AddDocument(std::vector<std::string>{"ухоженный", "пёс", "выразительные", "глаза"}, DocumentStatus::ACTUAL, std::vector<int>{4, 5, -12, 2, 1});

    auto resF = _container->FindTopDocuments(std::vector<std::string>{"пушистый", "ухоженный", "кот"}, DocumentStatus::ACTUAL, 3);
    std::vector<Document> result{Document{1, 0.650672, 5}, Document{2, 0.274653, 0}, Document{0, 0.101366, 2}};

    ASSERT_EQ(result.size(), resF.size());

    for (size_t i{0}; i < resF.size(); ++i)
    {
        EXPECT_EQ(result[i].id, resF[i].id);
        EXPECT_NEAR(result[i].relevance, resF[i].relevance, 0.0001);
        EXPECT_EQ(result[i].rating, resF[i].rating);
    }
}
