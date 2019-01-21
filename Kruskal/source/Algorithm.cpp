#include "Algorithm.hpp"

using namespace Kruskal;

Algorithm::Algorithm(const size_t a_height, const size_t a_width)
    : m_board(a_height, a_width)
{
    struct timeval time;
    gettimeofday(&time, 0);
    srand(time.tv_sec * 1000 + time.tv_usec % 1000);
}

Board& Algorithm::getBoard() {
    return m_board;
}

inline const size_t Algorithm::getRandom(const size_t a, const size_t b) const {
    return a + rand() % (b - a + 1);
}

void Algorithm::generateMaze() {
    using pii_t = std::pair<size_t, size_t>;
    std::vector<std::pair<pii_t, pii_t>> walls;

    for (size_t i = 0; i < getBoard().getHeight() - 1; ++i) {
        for (size_t j = 0; j < getBoard().getWidth() - 1; ++j) {
            walls.push_back({{i, j}, {i + 1, j}});
            walls.push_back({{i, j}, {i, j + 1}});
        }
    }

    std::random_shuffle(walls.begin(), walls.end());

    FindAndUnion fau(getBoard().getHeight() * getBoard().getWidth());

    for (auto & i : walls)
    {
        size_t a = i.first.first * getBoard().getWidth() + i.first.second;
        size_t b = i.second.first * getBoard().getWidth() + i.second.second;
        if (fau.Find(a) != fau.Find(b))
        {
            fau.Union(a, b);
            getBoard().getCell(i.first).addNeighbour(getBoard().getCell(i.first));
            getBoard().getCell(i.second).addNeighbour(getBoard().getCell(i.first));
        }
    }
}