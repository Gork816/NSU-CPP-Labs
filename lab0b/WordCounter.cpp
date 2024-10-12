#include "WordCounter.h"
#include <sstream>
#include <cctype>
#include <algorithm>

Counter::Counter() : totalCount(0) {}

std::string Counter::formatWord(const std::string& str) {
    std::string word;
    for (char ch : str) {
        if (isalpha(ch) || isdigit(ch)) {
            word += tolower(ch);
        }
        else if (!word.empty()) {
            break;
        }
    }
    return word;
}

void Counter::processLine(const std::string& line) {
    std::istringstream line_stream(line);
    std::string raw;
    std::string word;
    while (line_stream >> raw) {
        word = formatWord(raw);
        if (!word.empty()) {
            wordCount[word]++;
            totalCount++;
        }
    }
}

const std::map<std::string, int>& Counter::getWordCount() const {
    return wordCount;
}

int Counter::getTotalCount() const {
    return totalCount;
}