#pragma once

#include <vector>

namespace Kruskal
{

enum Direction 
{
	UP 		= 0,
	DOWN 	= 1,
	LEFT 	= 2,
	RIGHT 	= 3
};

class Cell
{
public:
	Cell() = delete;
	Cell(const size_t x, const size_t y);

	void addNeighbour(const Cell&);
	const std::vector<bool>& getNeighbour() const;

	size_t getX() const;
	size_t getY() const;

private:
	struct Position { size_t x, y; } m_position;
	std::vector<bool> m_neighbour;
};

}