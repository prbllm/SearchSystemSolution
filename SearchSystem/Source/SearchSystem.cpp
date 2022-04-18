#include <iostream>

// Self
#include "Algorithms.h"
#include "SearchSystemContainer.h"

#include <memory>

int main()
{
    // инициализация по умолчанию
    auto container = std::make_unique<SearchSystemContainer>();

    container->InitializeStopWords(std::set<std::string>{"и", "в", "на"});
    container->ClearDocuments();
    container->AddDocument(std::vector<std::string>{"белый", "кот", "и", "модный", "ошейник"}, std::vector<int>{2, 8, -3});
    container->AddDocument(std::vector<std::string>{"пушистый", "кот", "пушистый", "хвост"}, std::vector<int>{3, 7, 2, 7});
    container->AddDocument(std::vector<std::string>{"ухоженный", "пёс", "выразительные", "глаза"}, std::vector<int>{4, 5, -12, 2, 1});

    //container->InitializeStopWords(Algorithms::Algorithms::ReadLine());
	
    // Чтение документов
//    const int document_count = Algorithms::Algorithms::ReadLineWithNumber();
//    container->ClearDocuments();
//    for (int id = 0; id < document_count; ++id)
//        container->AddDocument(Algorithms::Algorithms::SplitIntoWords(Algorithms::Algorithms::ReadLine()));

    //auto query = Algorithms::Algorithms::SplitIntoWords(Algorithms::Algorithms::ReadLine());
   // auto query = std::vector<std::string>{"cheburashka", "with", "big", "ears", "likes", "oranges"};
   // for (const auto& doc : container->FindTopDocuments(query, 0))
    for (const auto& doc : container->FindTopDocuments(std::vector<std::string>{"пушистый", "ухоженный", "кот"}, 5))
        std::cout << "{ document_id = " << doc.id << ", relevance = " << doc.relevance << ", rating = " << doc.rating << " }" << std::endl;
}
