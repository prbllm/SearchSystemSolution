#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

// Self
#include "Algorithms.h"
#include "SearchSystemContainer.h"

#include <memory>

using namespace std;

vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words)
{
	vector<string> words;
    for (const string& word : Algorithms::Algorthms::SplitIntoWords(text))
    {
		if (stop_words.count(word) == 0) {
			words.push_back(word);
		}
	}
	return words;
}

void AddDocument(vector<pair<int, vector<string>>>& documents,
                 const set<string>& stop_words,
                 int document_id,
                 const string& document)
{
    vector<string> res;
    for (const string& word : SplitIntoWordsNoStop(document, stop_words))
        res.push_back(word);
    documents.push_back(std::make_pair(document_id, res));
}


int MatchDocument(const pair<int, vector<string>>& content,
                  const set<string>& query_words)
{
    int res{0};
    for (const auto& query_word : query_words)
    {
        for (const auto& word : content.second)
        {
            if (query_word == word)
            {
                ++res;
                break;
            }
        }
    }
    return res;
}

vector<pair<int, int>> FindDocuments(const vector<pair<int, vector<string>>>& documents,
                          const set<string>& stop_words,
                          const string& query)
{
    auto query_words = SplitIntoWordsNoStop(query, stop_words);
    auto query_unique = set<string>{query_words.begin(), query_words.end()};
    vector<pair<int, int>> result;

    for (const auto& doc : documents)
    {
        if (auto rel = MatchDocument(doc, query_unique); rel > 0)
            result.push_back(make_pair(doc.first, rel));
    }
    return result;
}


int main()
{
    using namespace Algorithms;
    auto container = std::make_unique<SearchSystemContainer>();

    // инициализация по умолчанию
    //container->InitializeStopWords(Algorthms::ReadLine());
	
    // Чтение документов
    vector<pair<int, vector<string>>> documents;
    const int document_count = Algorthms::ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id)
        AddDocument(documents, container->GetStopWords(), document_id, Algorithms::Algorthms::ReadLine());

    const string query = Algorithms::Algorthms::ReadLine();
    for (auto [document_id, relevance] : FindDocuments(documents, container->GetStopWords(), query))
        cout << "{ document_id = "s << document_id << ", relevance = "s << relevance << " }"s << endl;
}
