#include "CursorGame.hpp"

using namespace tutorial::basic::cursor;

CursorGame::CursorGame(int screenWidth, int screenHeight)
	: m_screenWidth(screenWidth)
	, m_screenHeight(screenHeight)
	, m_x(screenWidth / 2)
	, m_y(screenHeight / 2)
	, m_cursor(m_x, m_y)
{
}

void CursorGame::moveUp()
{
	moveTo(m_x, m_y - MOVE_STEP);
}

void CursorGame::moveDown()
{
	moveTo(m_x, m_y + MOVE_STEP);
}

void CursorGame::moveLeft()
{
	moveTo(m_x - MOVE_STEP, m_y);
}

void CursorGame::moveRight()
{
	moveTo(m_x + MOVE_STEP, m_y);
}

void CursorGame::reset()
{
	moveTo(m_screenWidth / 2, m_screenHeight / 2);
}

const Cursor& CursorGame::getCursor() const
{
	return m_cursor;
}

void CursorGame::moveTo(int x, int y)
{
	m_x = x;
	m_y = y;
	m_cursor = Cursor(m_x, m_y);
}
