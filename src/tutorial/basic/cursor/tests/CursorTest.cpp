#include "gtest/gtest.h"
#include "Cursor.hpp"

using namespace tutorial::basic::cursor;

TEST(CursorTest, ProducesFourArms)
{
	Cursor cursor(10, 10);
	EXPECT_EQ(cursor.getLines().size(), 4u);
}

TEST(CursorTest, ArmsAreLeftRightTopBottomAroundTheCenter)
{
	Cursor cursor(10, 10);
	const auto lines = cursor.getLines();

	std::vector<std::pair<int, int>> leftArm = { {5, 10}, {6, 10}, {7, 10}, {8, 10} };
	std::vector<std::pair<int, int>> rightArm = { {12, 10}, {13, 10}, {14, 10}, {15, 10} };
	std::vector<std::pair<int, int>> topArm = { {10, 5}, {10, 6}, {10, 7}, {10, 8} };
	std::vector<std::pair<int, int>> bottomArm = { {10, 12}, {10, 13}, {10, 14}, {10, 15} };

	EXPECT_EQ(lines[0].getPixels(), leftArm);
	EXPECT_EQ(lines[1].getPixels(), rightArm);
	EXPECT_EQ(lines[2].getPixels(), topArm);
	EXPECT_EQ(lines[3].getPixels(), bottomArm);
}

TEST(CursorTest, LeavesAGapAroundTheCenterPoint)
{
	Cursor cursor(10, 10);
	const auto center = std::make_pair(10, 10);

	for (const auto& line : cursor.getLines())
	{
		for (const auto& pixel : line.getPixels())
		{
			EXPECT_NE(pixel, center);
		}
	}
}

TEST(CursorTest, ArmsAreSymmetricAroundTheCenter)
{
	Cursor cursor(0, 0);
	const auto lines = cursor.getLines();
	const auto& leftArm = lines[0].getPixels();
	const auto& rightArm = lines[1].getPixels();
	const auto& topArm = lines[2].getPixels();
	const auto& bottomArm = lines[3].getPixels();

	ASSERT_EQ(leftArm.size(), rightArm.size());
	for (std::size_t i = 0; i < leftArm.size(); ++i)
	{
		const auto& mirrored = rightArm[rightArm.size() - 1 - i];
		EXPECT_EQ(leftArm[i].first, -mirrored.first);
		EXPECT_EQ(leftArm[i].second, mirrored.second);
	}

	ASSERT_EQ(topArm.size(), bottomArm.size());
	for (std::size_t i = 0; i < topArm.size(); ++i)
	{
		const auto& mirrored = bottomArm[bottomArm.size() - 1 - i];
		EXPECT_EQ(topArm[i].second, -mirrored.second);
		EXPECT_EQ(topArm[i].first, mirrored.first);
	}
}

TEST(CursorTest, WorksAtANonOriginPosition)
{
	Cursor cursor(-3, 7);
	const auto lines = cursor.getLines();

	std::vector<std::pair<int, int>> leftArm = { {-8, 7}, {-7, 7}, {-6, 7}, {-5, 7} };
	EXPECT_EQ(lines[0].getPixels(), leftArm);
}
