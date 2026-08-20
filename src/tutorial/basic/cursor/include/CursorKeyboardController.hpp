#ifndef TUTORIAL_BASIC_CURSOR_CURSOR_KEYBOARD_CONTROLLER_HPP
#define TUTORIAL_BASIC_CURSOR_CURSOR_KEYBOARD_CONTROLLER_HPP

#include "CursorGame.hpp"
#include "IKeyboardController.hpp"

namespace tutorial::basic::cursor
{
	class CursorKeyboardController : public screen::IKeyboardController
	{
	public:
		explicit CursorKeyboardController(CursorGame& cursorGame);

		void onArrowUp() override;
		void onArrowDown() override;
		void onArrowLeft() override;
		void onArrowRight() override;

	private:
		CursorGame& m_cursorGame;
	};
}

#endif // !TUTORIAL_BASIC_CURSOR_CURSOR_KEYBOARD_CONTROLLER_HPP
