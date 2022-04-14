#include <iostream>

// Self
#include "Algorithms.h"
#include "SearchSystemContainer.h"

#include <memory>

int main()
{
    using namespace Algorithms;

    // инициализация по умолчанию
    auto container = std::make_unique<SearchSystemContainer>();

    //container->InitializeStopWords(Algorthms::ReadLine());
	
    // Чтение документов
    //    const int document_count = Algorthms::ReadLineWithNumber();
    //    container->ClearDocuments();
    //    for (int id = 0; id < document_count; ++id)
    //        container->AddDocument(Algorthms::SplitIntoWords(Algorthms::ReadLine()));

    //auto query = Algorthms::SplitIntoWords(Algorthms::ReadLine());
    auto query = std::vector<std::string>{"cheburashka", "with", "big", "ears", "likes", "oranges"};
    for (auto [document_id, relevance] : container->FindDocuments(query))
        std::cout << "{ document_id = " << document_id << ", relevance = " << relevance << " }" << std::endl;
}
