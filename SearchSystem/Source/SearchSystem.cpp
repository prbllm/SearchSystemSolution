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
//        container->AddDocument(Algorithms::Algorithms::SplitIntoWords(Algorithms::Algorithms::ReadLine()));

    //auto query = Algorithms::Algorithms::SplitIntoWords(Algorithms::Algorithms::ReadLine());
    auto query = std::vector<std::string>{"cheburashka", "with", "big", "ears", "likes", "oranges"};
    for (const auto& doc : container->FindTopDocuments(query, 0))
        std::cout << "{ document_id = " << doc.id << ", relevance = " << doc.relevance << " }" << std::endl;
}
