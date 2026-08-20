#ifndef TUTORIAL_BASIC_CURSOR_LINE_HPP
#define TUTORIAL_BASIC_CURSOR_LINE_HPP

#include <vector>
#include <memory>
namespace tutorial::basic::cursor
{
	class Line
	{
	public:
		Line(std::pair<int, int> startPosition, std::pair<int, int> endPosition);

		std::vector<std::pair<int, int>> getPixels() const;
	private:
		std::vector<std::pair<int, int>> m_pixels;
	};
}

#endif // !TUTORIAL_BASIC_CURSOR_LINE_HPP