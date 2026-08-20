#ifndef TUTORIAL_BASIC_CURSOR_CURSOR_HPP
#define TUTORIAL_BASIC_CURSOR_CURSOR_HPP

#include "Line.hpp"
#include <vector>
#include <memory>

namespace tutorial::basic::cursor
{
	class Cursor
	{
	public:
		Cursor(int xPosition, int yPosition);
		std::vector<Line> getLines() const;
	private:
		std::pair<int, int> m_position;
		std::vector<Line> m_lines;
	};
}
#endif // !TUTORIAL_BASIC_CURSOR_CURSOR_HPP