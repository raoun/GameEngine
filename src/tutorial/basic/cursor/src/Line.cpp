#include "Line.hpp"
#include <cstdlib>

using namespace tutorial::basic::cursor;

Line::Line(std::pair<int, int> startPosition, std::pair<int, int> endPosition)
{
	int x0 = startPosition.first;
	int y0 = startPosition.second;
	const int x1 = endPosition.first;
	const int y1 = endPosition.second;

	const int dx = std::abs(x1 - x0);
	const int sx = x0 < x1 ? 1 : -1;
	const int dy = -std::abs(y1 - y0);
	const int sy = y0 < y1 ? 1 : -1;
	int error = dx + dy;

	while (true)
	{
		m_pixels.emplace_back(x0, y0);
		if (x0 == x1 && y0 == y1)
		{
			break;
		}

		const int doubledError = 2 * error;
		if (doubledError >= dy)
		{
			if (x0 == x1)
			{
				break;
			}
			error += dy;
			x0 += sx;
		}
		if (doubledError <= dx)
		{
			if (y0 == y1)
			{
				break;
			}
			error += dx;
			y0 += sy;
		}
	}
}

std::vector<std::pair<int, int>> Line::getPixels() const
{
	return m_pixels;
}
