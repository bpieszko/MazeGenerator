#pragma once

#include <cstdlib>
#include <vector>
#include "Cell.hpp"

namespace Kruskal
{

class Board
{
public:
    Board(const size_t height, const size_t width);

    Cell& getCell(const size_t x, const size_t y);
    Cell& getCell(const std::pair<size_t, size_t> p);

    size_t getHeight() const;
    size_t getWidth() const;

private:
    size_t m_height;
    size_t m_width;
    std::vector<std::vector<Cell>> m_cells;
};

class WrongCellPositionException : public std::exception
{
public:
    const char * what() const throw ()
    {
        return "Incorrent position of cell on the board.";
    }
};

}