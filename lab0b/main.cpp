#include <iostream>
#include <fstream>
#include "WordCounter.h"
#include "CSVWriter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Use word_count.exe input_stream.txt output.csv" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error while opening " << argv[1] << std::endl;
        return 1;
    }

    Counter counter;
    Writer writer;

    string line;
    while (getline(inputFile, line)) {
        counter.processLine(line);
    }

    inputFile.close();

    // Запись результатов в CSV-файл
    writer.writeToFile(argv[2], counter.getWordCount(), counter.getTotalCount());

    return 0;
}
