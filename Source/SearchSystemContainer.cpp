#include "SearchSystemContainer.h"

// Self
#include "Algorithms.h"

SearchSystemContainer::SearchSystemContainer()
{
    _stopWords = std::set<std::string>{"a", "an", "on", "the", "in", "is", "has", "been", "are", "with", "for", "from", "have", "be", "was"};
}

SearchSystemContainer::~SearchSystemContainer() = default;

const std::set<std::string> &SearchSystemContainer::GetStopWords() const
{
    return _stopWords;
}

void SearchSystemContainer::InitializeStopWords(const std::set<std::string>& words)
{
    _stopWords = words;
}

void SearchSystemContainer::InitializeStopWords(const std::string &words)
{
    if (words.empty())
        return;

    _stopWords.clear();
    for (const auto& word : Algorithms::Algorthms::SplitIntoWords(words))
        _stopWords.insert(word);
}

void SearchSystemContainer::InitializeStopWords(std::set<std::string> &&words)
{
    _stopWords = words;
}
