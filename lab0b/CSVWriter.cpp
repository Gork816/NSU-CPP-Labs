#include "CSVWriter.h"
#include <fstream>
#include <iostream>

void Writer::writeToFile(const std::string& fileName, const std::map<std::string, int>& wordCount, int totalWords) {
    std::ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        std::cerr << "Error while opening/creating file " << fileName << std::endl;
        return;
    }

    std::list<const std::pair<const std::string, int>*> sortedWordCount;
    for (const auto& pair : wordCount) {
        sortedWordCount.push_back(&pair);
    }

    sortedWordCount.sort([](const auto* a, const auto* b) {
        if (a->second != b->second)
            return a->second > b->second;
        return a->first < b->first;
        });

    outputFile << "Слово,Частота,Частота (%)" << std::endl;
    for (const auto* pair : sortedWordCount) {
        double frequency = (static_cast<double>(pair->second) / totalWords) * 100;
        outputFile << pair->first << ',' << pair->second << ',' << frequency << std::endl;
    }

    outputFile.close();
    std::cout << "File " << fileName << " successfully created" << std::endl;
}