#pragma once
#include <vector>
#include <set>
#include <iostream>


class Grid {
public:
    Grid();
    Grid(short w, short h);
    ~Grid();

    void print() const;
    void clear();

    void setCell(short x, short y, short value);
    short getCell(short x, short y) const;
    void incrementCell(short x, short y);
    std::set<std::pair<short, short>> getNeighbors(short x, short y) const;

    friend std::ostream& operator<<(std::ostream& out, const Grid& grid);
    friend std::istream& operator>>(std::istream& in, Grid& grid);

private:
    short width;
    short height;
    std::vector<short> cells;
};