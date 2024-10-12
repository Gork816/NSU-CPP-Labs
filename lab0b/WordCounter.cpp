#include "WordCounter.h"
#include <sstream>
#include <cctype>
#include <algorithm>

Counter::Counter() : totalCount(0) {}

void Counter::processLine(const std::string& line) {
    std::string word;
    for (char ch : line) {
        if (isalpha(ch) || isdigit(ch)) {
            word += tolower(ch);
        }
        else if (!word.empty()) {
            wordCount[word]++;
            totalCount++;
            word.clear();
        }
    }

    if (!word.empty()) {
        wordCount[word]++;
        totalCount++;
    }
}

const std::map<std::string, int>& Counter::getWordCount() const {
    return wordCount;
}

int Counter::getTotalCount() const {
    return totalCount;
}