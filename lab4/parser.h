#pragma once
#include <fstream>
#include <string>
#include <tuple>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <iostream>

template <typename... Args>
class CSVParser {
    std::istream& input;
    size_t skip_lines;
    char column_delimiter;
    char row_delimiter;
    char escape_char;

public:
    CSVParser(std::istream& stream, size_t skip = 0,
        char col_delim = ',', char row_delim = '\n', char esc_char = '"')
        : input(stream), skip_lines(skip), column_delimiter(col_delim),
        row_delimiter(row_delim), escape_char(esc_char) {
        for (size_t i = 0; i < skip_lines && input; ++i) {
            input.ignore(std::numeric_limits<std::streamsize>::max(), row_delimiter);
        }
    }

    class Iterator {
        std::istream* input;
        std::string current_line;
        std::tuple<Args...> current_tuple;
        size_t current_line_number = 0;
        char column_delimiter;
        char row_delimiter;
        char escape_char;
        bool has_error = false;

        void parse_line();

        template <std::size_t Index, typename Tuple>
        void parse_fields(std::istream& line_stream, Tuple& tuple);

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = std::tuple<Args...>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(std::istream* stream, char col_delim, char row_delim, char esc_char)
            : input(stream), column_delimiter(col_delim),
            row_delimiter(row_delim), escape_char(esc_char) {
            if (input && *input) {
                parse_line();
            }
        }

        Iterator() : input(nullptr), column_delimiter(','), row_delimiter('\n'), escape_char('"') {}

        value_type operator*() const { return current_tuple; }

        Iterator& operator++() {
            parse_line();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const { return input == other.input; }

        bool operator!=(const Iterator& other) const { return !(*this == other); }
    };

    Iterator begin() { return Iterator(&input, column_delimiter, row_delimiter, escape_char); }

    Iterator end() { return Iterator(); }
};

template <typename... Args>
void CSVParser<Args...>::Iterator::parse_line() {
    while (std::getline(*input, current_line)) {
        ++current_line_number;
        std::istringstream line_stream(current_line);

        try {
            parse_fields<0>(line_stream, current_tuple);
            return;
        }
        catch (const std::exception& e) {
            std::cerr << "Error on line " << current_line_number << ": " << e.what() << "\n";
            std::cerr << "Skipping line: " << current_line << "\n";
            continue;
        }
    }

    input = nullptr;
}

template <typename... Args>
template <std::size_t Index, typename Tuple>
void CSVParser<Args...>::Iterator::parse_fields(std::istream& line_stream, Tuple& tuple) {
    if constexpr (Index < std::tuple_size_v<Tuple>) {
        std::string field;
        char current_char;
        bool inside_quotes = false;
        std::string token;

        while (line_stream.get(current_char)) {
            if (current_char == escape_char) {
                inside_quotes = !inside_quotes;
            }
            else if (current_char == column_delimiter && !inside_quotes) {
                break;
            }
            else {
                token += current_char;
            }
        }

        if (!line_stream && token.empty() && !inside_quotes) {
            std::ostringstream oss;
            oss << "Malformed CSV: Not enough fields in line " << current_line_number;
            throw std::runtime_error(oss.str());
        }

        if (inside_quotes) {
            throw std::runtime_error("Malformed CSV: Unclosed quote at line " + std::to_string(current_line_number));
        }

        field = token;
        try {
            if constexpr (std::is_same_v<std::string, std::tuple_element_t<Index, Tuple>>) {
                std::get<Index>(tuple) = field;
            }
            else {
                std::istringstream field_stream(field);
                field_stream >> std::get<Index>(tuple);

                if (field_stream.fail() || !field_stream.eof()) {
                    throw std::runtime_error(
                        "Type mismatch at column " + std::to_string(Index + 1) +
                        ": Unable to convert field \"" + field + "\" to the expected type."
                    );
                }
            }
            parse_fields<Index + 1>(line_stream, tuple);
        }
        catch (const std::exception& e) {
            throw std::runtime_error(e.what());
        }
    }
    else {
        if (line_stream.peek() != EOF) {
            std::ostringstream oss;
            oss << "Malformed CSV: Too many fields in line " << current_line_number;
            throw std::runtime_error(oss.str());
        }
    }
}

