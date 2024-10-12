#pragma once

#include <string>
#include <map>
#include <list>

class Writer {
public:
    void writeToFile(const std::string& fileName, const std::map<std::string, int>& wordCount, int totalWords);
};