#include "Cell.hpp"

using namespace Kruskal;

Cell::Cell(const size_t a_x, const size_t a_y) : m_neighbour(4, false)
{
	m_position = {a_x, a_y};
}

void Cell::addNeighbour(const Cell& c)
{
	if (getX() > c.getX())
		m_neighbour.at(LEFT) = true;
	if (getX() < c.getX())
		m_neighbour.at(RIGHT) = true;
	if (getY() < c.getY())
		m_neighbour.at(UP) = true;
	if (getY() > c.getY())
		m_neighbour.at(DOWN) = true;
}

const std::vector<bool>& Cell::getNeighbour() const
{
	return m_neighbour;
}

size_t Cell::getX() const {
	return m_position.x;
}

size_t Cell::getY() const {
	return m_position.y;
}