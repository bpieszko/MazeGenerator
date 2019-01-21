#pragma once

#include <cstdlib>
#include <map>
#include <sys/time.h>
#include <algorithm>
#include "Board.hpp"
#include "FindAndUnion.hpp"

namespace Kruskal
{

class Algorithm
{
public:
	Algorithm(const size_t height, const size_t width);

	void generateMaze();
	Board& getBoard();

private:
	inline const size_t getRandom(const size_t a, const size_t b) const;
	Board m_board;
};

}