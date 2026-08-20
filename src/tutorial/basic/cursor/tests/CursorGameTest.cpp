#include "gtest/gtest.h"
#include "CursorGame.hpp"

using namespace tutorial::basic::cursor;

namespace
{
	std::pair<int, int> currentCenter(const CursorGame& game)
	{
		// The top arm of the cursor cross runs from (x, y - 5) to (x, y - 2),
		// so its first pixel identifies the cursor's current center.
		const auto topArmStart = game.getCursor().getLines()[2].getPixels().front();
		return { topArmStart.first, topArmStart.second + 5 };
	}
}

TEST(CursorGameTest, DefaultsToTheMiddleOfTheScreen)
{
	CursorGame game(1280, 720);
	EXPECT_EQ(currentCenter(game), std::make_pair(640, 360));
}

TEST(CursorGameTest, MoveUpShiftsTheCursorTenPixelsUp)
{
	CursorGame game(1280, 720);
	game.moveUp();
	EXPECT_EQ(currentCenter(game), std::make_pair(640, 350));
}

TEST(CursorGameTest, MoveDownShiftsTheCursorTenPixelsDown)
{
	CursorGame game(1280, 720);
	game.moveDown();
	EXPECT_EQ(currentCenter(game), std::make_pair(640, 370));
}

TEST(CursorGameTest, MoveLeftShiftsTheCursorTenPixelsLeft)
{
	CursorGame game(1280, 720);
	game.moveLeft();
	EXPECT_EQ(currentCenter(game), std::make_pair(630, 360));
}

TEST(CursorGameTest, MoveRightShiftsTheCursorTenPixelsRight)
{
	CursorGame game(1280, 720);
	game.moveRight();
	EXPECT_EQ(currentCenter(game), std::make_pair(650, 360));
}

TEST(CursorGameTest, MovesAccumulateAcrossCalls)
{
	CursorGame game(1280, 720);
	game.moveRight();
	game.moveRight();
	game.moveDown();
	EXPECT_EQ(currentCenter(game), std::make_pair(660, 370));
}

TEST(CursorGameTest, ResetReturnsTheCursorToTheMiddleOfTheScreen)
{
	CursorGame game(1280, 720);
	game.moveUp();
	game.moveLeft();
	game.moveLeft();

	game.reset();

	EXPECT_EQ(currentCenter(game), std::make_pair(640, 360));
}
