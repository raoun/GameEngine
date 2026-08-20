#include "gtest/gtest.h"
#include "CursorGame.hpp"
#include "CursorKeyboardController.hpp"

using namespace tutorial::basic::cursor;

namespace
{
	std::pair<int, int> currentCenter(const CursorGame& game)
	{
		const auto topArmStart = game.getCursor().getLines()[2].getPixels().front();
		return { topArmStart.first, topArmStart.second + 5 };
	}
}

TEST(CursorKeyboardControllerTest, OnArrowUpMovesTheCursorGameUp)
{
	CursorGame game(1280, 720);
	CursorKeyboardController controller(game);

	controller.onArrowUp();

	EXPECT_EQ(currentCenter(game), std::make_pair(640, 350));
}

TEST(CursorKeyboardControllerTest, OnArrowDownMovesTheCursorGameDown)
{
	CursorGame game(1280, 720);
	CursorKeyboardController controller(game);

	controller.onArrowDown();

	EXPECT_EQ(currentCenter(game), std::make_pair(640, 370));
}

TEST(CursorKeyboardControllerTest, OnArrowLeftMovesTheCursorGameLeft)
{
	CursorGame game(1280, 720);
	CursorKeyboardController controller(game);

	controller.onArrowLeft();

	EXPECT_EQ(currentCenter(game), std::make_pair(630, 360));
}

TEST(CursorKeyboardControllerTest, OnArrowRightMovesTheCursorGameRight)
{
	CursorGame game(1280, 720);
	CursorKeyboardController controller(game);

	controller.onArrowRight();

	EXPECT_EQ(currentCenter(game), std::make_pair(650, 360));
}
