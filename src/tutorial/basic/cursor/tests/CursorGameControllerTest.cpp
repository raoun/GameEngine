#include "gtest/gtest.h"
#include "CursorGame.hpp"
#include "CursorGameController.hpp"
#include "CursorKeyboardController.hpp"
#include <windows.h>

using namespace tutorial::basic::cursor;

TEST(CursorGameControllerTest, ExposesTheProvidedKeyboardController)
{
	CursorGame game(100, 100);
	CursorKeyboardController keyboardController(game);
	CursorGameController controller(game, keyboardController);

	EXPECT_EQ(controller.getKeyboardController(), static_cast<screen::IKeyboardController*>(&keyboardController));
}

TEST(CursorGameControllerTest, OnResetDelegatesToTheCursorGame)
{
	CursorGame game(100, 100);
	CursorKeyboardController keyboardController(game);
	CursorGameController controller(game, keyboardController);

	game.moveUp();
	game.moveLeft();

	controller.onReset();

	const auto topArmStart = game.getCursor().getLines()[2].getPixels().front();
	EXPECT_EQ(std::make_pair(topArmStart.first, topArmStart.second + 5), std::make_pair(50, 50));
}

TEST(CursorGameControllerTest, OnPaintDrawsTheCursorPixelsInRed)
{
	CursorGame game(100, 100);
	CursorKeyboardController keyboardController(game);
	CursorGameController controller(game, keyboardController);

	HDC screenDeviceContext = GetDC(nullptr);
	HDC memoryDeviceContext = CreateCompatibleDC(screenDeviceContext);
	HBITMAP bitmap = CreateCompatibleBitmap(screenDeviceContext, 100, 100);
	HGDIOBJ previousBitmap = SelectObject(memoryDeviceContext, bitmap);

	controller.onPaint(memoryDeviceContext);

	// The left arm of the cursor cross (centered on (50, 50)) covers x in [45, 48] at y == 50.
	EXPECT_EQ(GetPixel(memoryDeviceContext, 45, 50), RGB(255, 0, 0));
	// A point away from any arm is left untouched (black, the default bitmap contents).
	EXPECT_EQ(GetPixel(memoryDeviceContext, 10, 10), RGB(0, 0, 0));

	SelectObject(memoryDeviceContext, previousBitmap);
	DeleteObject(bitmap);
	DeleteDC(memoryDeviceContext);
	ReleaseDC(nullptr, screenDeviceContext);
}
