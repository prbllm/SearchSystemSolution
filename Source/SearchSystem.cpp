#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

// Self
#include "Algorithms.h"

using namespace std;

vector<string> SplitIntoWords(const string& text)
{
    vector<string> words;
    string word;
    for (const char c : text)
    {
        if (c == ' ')
        {
            if (!word.empty())
            {
                words.push_back(word);
                word.clear();
            }
        }
        else
        {
            word += c;
        }
    }
    if (!word.empty())
    {
        words.push_back(word);
    }

    return words;
}

set<string> ParseStopWords(const string& text)
{
	set<string> stop_words;
    for (const string& word : SplitIntoWords(text))
    {
		stop_words.insert(word);
	}
    return stop_words;
}

vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words)
{
	vector<string> words;
    for (const string& word : SplitIntoWords(text))
    {
		if (stop_words.count(word) == 0) {
			words.push_back(word);
		}
	}
	return words;
}

void AddDocument(map<string, set<int>>& word_to_documents,
                 const set<string>& stop_words,
                 int document_id,
                 const string& document)
{
    for (const string& word : SplitIntoWordsNoStop(document, stop_words))
    {
		word_to_documents[word].insert(document_id);
	}
}

vector<pair<int, int>> FindDocuments(const map<string, set<int>>& word_to_documents,
                          const set<string>& stop_words,
                          const string& query)
{
	const vector<string> query_words = SplitIntoWordsNoStop(query, stop_words);
	map<int, int> document_ids;
	for (const string& word : query_words)
    {
		if (!word_to_documents.count(word))
			continue;
        
		for (const int document_id : word_to_documents.at(word))
			++document_ids[document_id];
	}
	
    vector<pair<int, int>> res;
    for (const auto& p : document_ids)
    {
        res.push_back(p);
    }
	return res;
}


int main()
{
    using namespace Algorithms;

    const string stop_words_joined = Algorthms::ReadLine();
	const set<string> stop_words = ParseStopWords(stop_words_joined);
	
	// Read documents
	map<string, set<int>> word_to_documents;
    const int document_count = Algorthms::ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id)
        AddDocument(word_to_documents, stop_words, document_id, Algorithms::Algorthms::ReadLine());

    const string query = Algorithms::Algorthms::ReadLine();
    for (auto [document_id, relevance] : FindDocuments(word_to_documents, stop_words, query))
        cout << "{ document_id = "s << document_id << ", relevance = "s << relevance << " }"s << endl;
}