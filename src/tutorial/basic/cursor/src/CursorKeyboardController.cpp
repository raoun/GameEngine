#include "CursorKeyboardController.hpp"

using namespace tutorial::basic::cursor;

CursorKeyboardController::CursorKeyboardController(CursorGame& cursorGame)
	: m_cursorGame(cursorGame)
{
}

void CursorKeyboardController::onArrowUp()
{
	m_cursorGame.moveUp();
}

void CursorKeyboardController::onArrowDown()
{
	m_cursorGame.moveDown();
}

void CursorKeyboardController::onArrowLeft()
{
	m_cursorGame.moveLeft();
}

void CursorKeyboardController::onArrowRight()
{
	m_cursorGame.moveRight();
}
