#include "gtest/gtest.h"
#include "Line.hpp"

using namespace tutorial::basic::cursor;

TEST(LineTest, SinglePointWhenStartEqualsEnd)
{
	Line line({ 2, 3 }, { 2, 3 });
	std::vector<std::pair<int, int>> expected = { {2, 3} };
	EXPECT_EQ(line.getPixels(), expected);
}

TEST(LineTest, HorizontalLineAscending)
{
	Line line({ 0, 5 }, { 4, 5 });
	std::vector<std::pair<int, int>> expected = { {0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5} };
	EXPECT_EQ(line.getPixels(), expected);
}

TEST(LineTest, HorizontalLineDescending)
{
	Line line({ 4, 5 }, { 0, 5 });
	std::vector<std::pair<int, int>> expected = { {4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5} };
	EXPECT_EQ(line.getPixels(), expected);
}

TEST(LineTest, VerticalLine)
{
	Line line({ 3, 0 }, { 3, 4 });
	std::vector<std::pair<int, int>> expected = { {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4} };
	EXPECT_EQ(line.getPixels(), expected);
}

TEST(LineTest, DiagonalLineAscending)
{
	Line line({ 0, 0 }, { 2, 2 });
	std::vector<std::pair<int, int>> expected = { {0, 0}, {1, 1}, {2, 2} };
	EXPECT_EQ(line.getPixels(), expected);
}

TEST(LineTest, DiagonalLineWithNegativeDirection)
{
	Line line({ 2, 5 }, { 0, 3 });
	std::vector<std::pair<int, int>> expected = { {2, 5}, {1, 4}, {0, 3} };
	EXPECT_EQ(line.getPixels(), expected);
}

TEST(LineTest, ShallowDiagonalDoesNotFillARectangle)
{
	// dx = 4, dy = 2: a true line has max(dx, dy) + 1 = 5 pixels.
	// A (buggy) rectangle-fill would instead produce (dx + 1) * (dy + 1) = 15.
	Line line({ 0, 0 }, { 4, 2 });
	const auto pixels = line.getPixels();

	EXPECT_EQ(pixels.size(), 5u);
	EXPECT_EQ(pixels.front(), std::make_pair(0, 0));
	EXPECT_EQ(pixels.back(), std::make_pair(4, 2));

	for (std::size_t i = 1; i < pixels.size(); ++i)
	{
		const int stepX = pixels[i].first - pixels[i - 1].first;
		const int stepY = pixels[i].second - pixels[i - 1].second;

		EXPECT_GE(stepX, 0);
		EXPECT_LE(stepX, 1);
		EXPECT_GE(stepY, 0);
		EXPECT_LE(stepY, 1);
		EXPECT_TRUE(stepX != 0 || stepY != 0);
	}
}
