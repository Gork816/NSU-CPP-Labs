#include "pch.h"
#include "C:\Users\79222\Desktop\NSU-CPP-Labs\lab2\grid.cpp"
#include "C:\Users\79222\Desktop\NSU-CPP-Labs\lab2\game.cpp"
#include "C:\Users\79222\Desktop\NSU-CPP-Labs\lab2\filemanager.cpp"

TEST(GridTest, DefaultConstructor) {
    Grid grid;
    EXPECT_EQ(grid.getCell(0, 0), 0);
}

TEST(GridTest, ParameterizedConstructor) {
    Grid grid(10, 5);
    EXPECT_EQ(grid.getCell(0, 0), 0);
}

TEST(GridTest, Clear) {
    Grid grid(5, 5);
    grid.setCell(2, 2, 1);
    grid.clear();
    for (short x = 0; x < 5; ++x) {
        for (short y = 0; y < 5; ++y) {
            EXPECT_EQ(grid.getCell(x, y), 0);
        }
    }
}

TEST(GridTest, SetAndGetCell) {
    Grid grid(3, 3);
    grid.setCell(1, 1, 42);
    EXPECT_EQ(grid.getCell(1, 1), 42);

    EXPECT_THROW(grid.setCell(3, 3, 10), std::out_of_range);
    EXPECT_THROW(grid.getCell(3, 3), std::out_of_range);
}

TEST(GridTest, IncrementCell) {
    Grid grid(3, 3);
    grid.incrementCell(1, 1);
    EXPECT_EQ(grid.getCell(1, 1), 1);
    grid.incrementCell(1, 1);
    EXPECT_EQ(grid.getCell(1, 1), 2);

    EXPECT_THROW(grid.incrementCell(3, 3), std::out_of_range);
}

TEST(GridTest, GetNeighbors) {
    Grid grid(3, 3);

    auto neighbors = grid.getNeighbors(1, 1);
    std::set<std::pair<short, short>> expected = {
        {0, 0}, {0, 1}, {0, 2},
        {1, 0},         {1, 2},
        {2, 0}, {2, 1}, {2, 2}
    };
    EXPECT_EQ(neighbors, expected);

    neighbors = grid.getNeighbors(0, 0);
    expected = {
        {2, 2}, {2, 0}, {2, 1},
        {0, 2},         {0, 1},
        {1, 2}, {1, 0}, {1, 1}
    };
    EXPECT_EQ(neighbors, expected);

    neighbors = grid.getNeighbors(2, 2);
    expected = {
        {1, 1}, {1, 2}, {1, 0},
        {2, 1},         {2, 0},
        {0, 1}, {0, 2}, {0, 0}
    };
    EXPECT_EQ(neighbors, expected);

    EXPECT_THROW(grid.getNeighbors(3, 3), std::out_of_range);
}

TEST(GridTest, Print) {
    Grid grid(2, 2);
    grid.setCell(0, 0, 1);
    grid.setCell(1, 1, 2);

    testing::internal::CaptureStdout();
    grid.print();
    std::string output = testing::internal::GetCapturedStdout();

    std::string expectedOutput =
        "O . \n"
        ". O \n";
    EXPECT_EQ(output, expectedOutput);
}

TEST(GenerationTest, Test1) {
    Game game;
    FileManager fm;
    fm.loadFromFile("C:/Users/79222/Desktop/NSU-CPP-Labs/lab2_tests/x64/Debug/test1.txt");
    game.initializeFieldFromFile(fm);

    std::set<std::pair<short, short>> expected = { {1, 0}, {0, 1}, {2, 1}, {1, 2} };
    std::set<std::pair<short, short>> cells = game.getAliveCells();
    EXPECT_EQ(cells, expected);

    game.processGeneration();

    cells = game.getAliveCells();
    expected = { {0, 0}, {0, 2}, {1, 1}, { 2, 0 }, {2, 2} };
    EXPECT_EQ(cells, expected);
}