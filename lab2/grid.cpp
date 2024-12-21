#include "grid.h"
#include <iostream>


Grid::Grid() : width(10), height(10), cells(10 * 10, 0) {}

Grid::Grid(short w, short h) : width(w), height(h), cells(w*h, 0) {}

Grid::~Grid() {}

void Grid::print() const {
    for (short i = 0; i < height; ++i) {
        for (short j = 0; j < width; ++j) {
            std::cout << (cells[i * width + j] ? 'O' : '.') << ' ';
        }
        std::cout << '\n';
    }
}

void Grid::setCell(short x, short y, short value) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Grid::setCell - index out of range");
    }
    cells[y * width + x] = value;
}

short Grid::getCell(short x, short y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Grid::getCell - index out of range");
    }
    return cells[y * width + x];
}

void Grid::incrementCell(short x, short y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Grid::incrementCell - index out of range");
    }
    cells[y * width + x]++;
}

void Grid::clear() {
    for (short i = 0; i < height*width; ++i) {
        cells[i] = 0;
    }
}

std::set<std::pair<short, short>> Grid::getNeighbors(short x, short y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Grid::getNeighbors - index out of range");
    }
    
    std::set<std::pair<short, short>> neighbors;
    const short dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    const short dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (short i = 0; i < 8; ++i) {
        short nx = (x + dx[i] + width) % width;
        short ny = (y + dy[i] + height) % height;
        neighbors.emplace(nx, ny);
    }

    return neighbors;
}

std::ostream& operator<<(std::ostream& out, const Grid& grid) {
    out << grid.width << " " << grid.height << "\n";
    for (short x = 0; x < grid.width; ++x) {
        for (short y = 0; y < grid.height; ++y) {
            out << grid.getCell(x, y);
            if (y != grid.height - 1) {
                out << ' ';
            }
        }
        out << "\n";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Grid& grid) {
    short width, height;
    in >> width >> height;
    grid = Grid(width, height);

    for (short x = 0; x < width; ++x) {
        for (short y = 0; y < height; ++y) {
            short value;
            in >> value;
            grid.setCell(x, y, value);
        }
    }
    return in;
}
