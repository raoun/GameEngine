#include "Cursor.hpp"

using namespace tutorial::basic::cursor;

Cursor::Cursor(int xPosition, int yPosition) : m_position(xPosition, yPosition) 
{
	m_lines.emplace_back(std::make_pair(xPosition - 5, yPosition ), std::make_pair(xPosition - 2, yPosition ));
	m_lines.emplace_back(std::make_pair(xPosition + 2, yPosition ), std::make_pair(xPosition + 5, yPosition ));
	m_lines.emplace_back(std::make_pair(xPosition, yPosition - 5 ), std::make_pair(xPosition, yPosition - 2 ));
	m_lines.emplace_back(std::make_pair(xPosition, yPosition + 2 ), std::make_pair(xPosition, yPosition + 5 ));
}

std::vector<Line> Cursor::getLines() const
{ 
	return m_lines;
}
