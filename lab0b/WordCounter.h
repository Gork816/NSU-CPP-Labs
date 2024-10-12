#pragma once

#include <map>
#include <string>


class Counter {
private:
    std::map<std::string, int> wordCount;
    int totalCount;

public:
    Counter();
    void processLine(const std::string& line);
    const std::map<std::string, int>& getWordCount() const;
    int getTotalCount() const;

private:
    std::string formatWord(const std::string& str);  // Вспомогательная функция для выделения слов
};