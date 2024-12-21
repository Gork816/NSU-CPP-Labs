#include "pch.h"
#include <sstream>
#include "C:\Users\79222\Desktop\NSU-CPP-Labs\lab4\parser.h"
#include "C:\Users\79222\Desktop\NSU-CPP-Labs\lab4\print_tuple.h"


TEST(CSVParserTest, BasicParsing) {
    std::istringstream input("1,Hello,3.14\n2,World,2.71");
    CSVParser<int, std::string, double> parser(input);

    auto it = parser.begin();
    ASSERT_EQ(std::get<0>(*it), 1);
    ASSERT_EQ(std::get<1>(*it), "Hello");
    ASSERT_DOUBLE_EQ(std::get<2>(*it), 3.14);

    ++it;
    ASSERT_EQ(std::get<0>(*it), 2);
    ASSERT_EQ(std::get<1>(*it), "World");
    ASSERT_DOUBLE_EQ(std::get<2>(*it), 2.71);
}

TEST(CSVParserTest, EscapedQuotes) {
    std::istringstream input("1,+Hello, World+,3.14\n2,+Goodbye, World+,2.71");
    CSVParser<int, std::string, double> parser(input, 0, ',', '\n', '+');

    auto it = parser.begin();
    ASSERT_EQ(std::get<1>(*it), "Hello, World");

    ++it;
    ASSERT_EQ(std::get<1>(*it), "Goodbye, World");
}

TEST(CSVParserTest, CustomDelimiters) {
    std::istringstream input("1;Hello;3.14\n2;World;2.71");
    CSVParser<int, std::string, double> parser(input, 0, ';', '\n');

    auto it = parser.begin();
    ASSERT_EQ(std::get<0>(*it), 1);
    ASSERT_EQ(std::get<1>(*it), "Hello");
    ASSERT_DOUBLE_EQ(std::get<2>(*it), 3.14);

    ++it;
    ASSERT_EQ(std::get<0>(*it), 2);
    ASSERT_EQ(std::get<1>(*it), "World");
    ASSERT_DOUBLE_EQ(std::get<2>(*it), 2.71);
}

TEST(CSVParserTest, MalformedCSV1) {
    std::istringstream input("1,Hello\n2,World,2.71");

    CSVParser<int, std::string, double> parser(input);

    auto it = parser.begin();
    ASSERT_EQ(std::get<0>(*it), 2); // Первую строку пропущена из-за неккоректного кол-ва элементов
    ASSERT_EQ(std::get<1>(*it), "World");
    ASSERT_EQ(std::get<2>(*it), 2.71);
}

TEST(CSVParserTest, MalformedCSV2) {
    std::istringstream input("1,Hello,lol\n2,World,2.71");

    CSVParser<int, std::string, double> parser(input);

    auto it = parser.begin();
    ++it;
    ASSERT_EQ(std::get<0>(*it), 2); // Первая строка пропущена из-за ошибки в третьем столбце
    ASSERT_EQ(std::get<1>(*it), "World");
    ASSERT_EQ(std::get<2>(*it), 2.71);
}

TEST(CSVParserTest, MalformedCSV3) {
    std::istringstream input("1,\"Hello,3.14\n2,World,2.71");

    CSVParser<int, std::string, double> parser(input);

    auto it = parser.begin();
    ASSERT_EQ(std::get<0>(*it), 2); // Первая строка пропущена из-за незакрытой кавычки
    ASSERT_EQ(std::get<1>(*it), "World");
    ASSERT_EQ(std::get<2>(*it), 2.71);
}

TEST(CSVParserTest, SkipLines) {
    std::istringstream input("Skip this line\n1,Hello,3.14\n2,World,2.71");
    CSVParser<int, std::string, double> parser(input, 1);

    auto it = parser.begin();
    ASSERT_EQ(std::get<0>(*it), 1);
    ASSERT_EQ(std::get<1>(*it), "Hello");
    ASSERT_DOUBLE_EQ(std::get<2>(*it), 3.14);
}

TEST(CSVParserTest, EmptyInput) {
    std::istringstream input("");
    CSVParser<int, std::string, double> parser(input);

    auto it = parser.begin();
    ASSERT_EQ(it, parser.end());
}

TEST(CSVParserTest, SingleRow) {
    std::istringstream input("1,Hello,3.14");
    CSVParser<int, std::string, double> parser(input);

    auto it = parser.begin();
    ASSERT_EQ(std::get<0>(*it), 1);
    ASSERT_EQ(std::get<1>(*it), "Hello");
    ASSERT_DOUBLE_EQ(std::get<2>(*it), 3.14);

    ++it;
    ASSERT_EQ(it, parser.end());
}