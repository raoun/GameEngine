#ifndef TUTORIAL_BASIC_CURSOR_CURSOR_GAME_CONTROLLER_HPP
#define TUTORIAL_BASIC_CURSOR_CURSOR_GAME_CONTROLLER_HPP

#include "CursorGame.hpp"
#include "CursorKeyboardController.hpp"
#include "IWindowController.hpp"

namespace tutorial::basic::cursor
{
	class CursorGameController : public screen::IWindowController
	{
	public:
		CursorGameController(CursorGame& cursorGame, CursorKeyboardController& keyboardController);

		void update() override;
		void onPaint(HDC deviceContext) override;
		void onDestroy() override;
		void onReset() override;

		screen::IKeyboardController* getKeyboardController() const override;

	private:
		CursorGame& m_cursorGame;
		CursorKeyboardController& m_keyboardController;
	};
}

#endif // !TUTORIAL_BASIC_CURSOR_CURSOR_GAME_CONTROLLER_HPP
