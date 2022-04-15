#include <iostream>

// Self
#include "Algorithms.h"
#include "SearchSystemContainer.h"

#include <memory>

int main()
{
    // инициализация по умолчанию
    auto container = std::make_unique<SearchSystemContainer>();

    //container->InitializeStopWords(Algorithms::Algorithms::ReadLine());
	
    // Чтение документов
    //    const int document_count = Algorithms::Algorithms::ReadLineWithNumber();
    //    container->ClearDocuments();
    //    for (int id = 0; id < document_count; ++id)
    //        container->AddDocument(Algorthms::SplitIntoWords(Algorithms::Algorithms::ReadLine()));

    //auto query = Algorthms::SplitIntoWords(Algorithms::Algorithms::ReadLine());
    auto query = std::vector<std::string>{"cheburashka", "with", "big", "ears", "likes", "oranges"};
    for (auto [document_id, relevance] : container->FindTopDocuments(query, 1))
        std::cout << "{ document_id = " << document_id << ", relevance = " << relevance << " }" << std::endl;
}
