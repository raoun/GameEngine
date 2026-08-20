#include "CursorGameController.hpp"

using namespace tutorial::basic::cursor;

CursorGameController::CursorGameController(CursorGame& cursorGame, CursorKeyboardController& keyboardController)
	: m_cursorGame(cursorGame)
	, m_keyboardController(keyboardController)
{
}

void CursorGameController::update()
{
}

void CursorGameController::onPaint(HDC deviceContext)
{
	for (const auto& line : m_cursorGame.getCursor().getLines())
	{
		for (const auto& pixel : line.getPixels())
		{
			SetPixel(deviceContext, pixel.first, pixel.second, RGB(255, 0, 0));
		}
	}
}

void CursorGameController::onDestroy()
{
}

void CursorGameController::onReset()
{
	m_cursorGame.reset();
}

screen::IKeyboardController* CursorGameController::getKeyboardController() const
{
	return &m_keyboardController;
}
