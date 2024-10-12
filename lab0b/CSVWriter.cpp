#include "CSVWriter.h"
#include <fstream>
#include <iostream>

std::list<std::pair<std::string, int>> Writer::sortWords(const std::map<std::string, int>& wordCount) {
    // Переносим данные из map в список пар
    std::list<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());

    // Сортировка списка по убыванию частоты
    sortedWords.sort([](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return b.second < a.second;
        });

    return sortedWords;
}

void Writer::writeToFile(const std::string& fileName, const std::map<std::string, int>& wordCount, int totalWords) {
    std::ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        std::cerr << "Error while opening/creating file " << fileName << std::endl;
        return;
    }

    std::list<std::pair<std::string, int>> sortedWordCount = sortWords(wordCount);

    outputFile << "Слово,Частота,Частота (%)" << std::endl;
    for (const auto& pair : sortedWordCount) {
        double frequency = (static_cast<double>(pair.second) / totalWords) * 100;
        outputFile << pair.first << ',' << pair.second << ',' << frequency << std::endl;
    }

    outputFile.close();
    std::cout << "File " << fileName << " successfully created" << std::endl;
}