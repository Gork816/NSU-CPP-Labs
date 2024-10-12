#pragma once

#include <string>
#include <map>
#include <list>

class Writer {
public:
    void writeToFile(const std::string& fileName, const std::map<std::string, int>& wordCount, int totalWords);
private:
    std::list<std::pair<std::string, int>> sortWords(const std::map<std::string, int>& wordCount);
};