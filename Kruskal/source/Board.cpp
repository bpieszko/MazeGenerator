#include "Board.hpp"

using namespace Kruskal;

Board::Board(const size_t a_height, const size_t a_width) {
    m_height = a_height;
    m_width = a_width;

    m_cells.resize(a_height, std::vector<Cell>(a_width, Cell(0, 0)));
    int cnt_h = 0, cnt_w = 0;
    for (auto & i : m_cells) {
        cnt_w = 0;
        for (auto & j : i) {
            j = Cell(cnt_h, cnt_w);
            ++cnt_w;
        }
        ++cnt_h;
    }
}

Cell& Board::getCell(const size_t x, const size_t y) {
    if (x >= m_height || y >= m_width)
        throw WrongCellPositionException();
    return m_cells.at(x).at(y);
}

Cell& Board::getCell(const std::pair<size_t, size_t> p) {
    return getCell(p.first, p.second);
}

size_t Board::getHeight() const {
    return m_height;
}

size_t Board::getWidth() const {
    return m_width;
}