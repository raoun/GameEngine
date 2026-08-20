#ifndef TUTORIAL_BASIC_CURSOR_CURSOR_GAME_HPP
#define TUTORIAL_BASIC_CURSOR_CURSOR_GAME_HPP

#include "Cursor.hpp"

namespace tutorial::basic::cursor
{
	class CursorGame
	{
	public:
		static constexpr int MOVE_STEP = 10;

		CursorGame(int screenWidth, int screenHeight);

		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();

		void reset();

		const Cursor& getCursor() const;

	private:
		void moveTo(int x, int y);

		int m_screenWidth;
		int m_screenHeight;
		int m_x;
		int m_y;
		Cursor m_cursor;
	};
}

#endif // !TUTORIAL_BASIC_CURSOR_CURSOR_GAME_HPP
