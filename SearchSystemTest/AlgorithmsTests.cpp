#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../SearchSystem/Include/Algorithms.h"

using namespace testing;

TEST(AlgorithmsTests, SplitIntoWordsTest)
{
    EXPECT_EQ((std::vector<std::string>{"asd", "dsa", "zxc"})
              , Algorithms::Algorithms::SplitIntoWords("asd dsa zxc"));
}

TEST(AlgorithmsTests, CountStartsWithTest)
{
    EXPECT_EQ(0, Algorithms::Algorithms::CountStartsWith(std::vector<std::string>{"asd", "dsa", "zxc"}, 'c'));
    EXPECT_EQ(0, Algorithms::Algorithms::CountStartsWith(std::vector<std::string>{}, 'c'));
    EXPECT_EQ(1, Algorithms::Algorithms::CountStartsWith(std::vector<std::string>{"asd", "dsa", "zxc"}, 'a'));
    EXPECT_EQ(3, Algorithms::Algorithms::CountStartsWith(std::vector<std::string>{"dasd", "dsa", "d"}, 'd'));
}

TEST(AlgorithmsTests, CCalculateMedianTest)
{
    EXPECT_EQ(std::make_pair(true, 2.0)
              , Algorithms::Algorithms::CalculateMedian(std::vector<double>{1, 2, 3}));
    EXPECT_EQ(std::make_pair(true, 2.5)
              , Algorithms::Algorithms::CalculateMedian(std::vector<double>{1, 2, 3, 4}));
    EXPECT_EQ(std::make_pair(false, 0.0)
              , Algorithms::Algorithms::CalculateMedian(std::vector<double>{}));
}

TEST(AlgorithmsTests, TransformStringToCaseTest)
{
    EXPECT_EQ("", Algorithms::Algorithms::TransformStringToCase("", true));
    EXPECT_EQ("", Algorithms::Algorithms::TransformStringToCase("", false));
    EXPECT_EQ("a", Algorithms::Algorithms::TransformStringToCase("a", true));
    EXPECT_EQ("a", Algorithms::Algorithms::TransformStringToCase("A", true));
    EXPECT_EQ("A", Algorithms::Algorithms::TransformStringToCase("a", false));
    EXPECT_EQ("A", Algorithms::Algorithms::TransformStringToCase("A", false));
    EXPECT_EQ("AAAAAAA", Algorithms::Algorithms::TransformStringToCase("AaAaAaa", false));
    EXPECT_EQ("aaaaaaaaaa", Algorithms::Algorithms::TransformStringToCase("aAaAaaaAAA", true));
}

TEST(AlgorithmsTests, LexicographicalSortingTest)
{
    std::vector<std::string> res{"quantity", "AMOUNT", "Selection", "Search"};
    Algorithms::Algorithms::LexicographicalSorting(res);
    EXPECT_EQ(res, (std::vector<std::string>{"AMOUNT", "quantity", "Search", "Selection"}));
}
