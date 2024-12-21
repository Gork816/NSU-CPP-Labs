#include "parser.h"
#include "print_tuple.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0]
                << " <filename> [column_delimiter] [row_delimiter] [escape_char]\n";
            return 1;
        }

        std::string filename = argv[1];

        char column_delimiter = ','; 
        char row_delimiter = '\n'; 
        char escape_char = '"'; 

        if (argc > 2) column_delimiter = argv[2][0];
        if (argc > 3) row_delimiter = argv[3][0];
        if (argc > 4) escape_char = argv[4][0];

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << "\n";
            return 1;
        }

        CSVParser<int, std::string, double> parser(file, 1, column_delimiter, row_delimiter, escape_char);

        for (const auto& row : parser) {
            std::cout << row << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
