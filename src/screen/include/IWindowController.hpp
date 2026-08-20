#ifndef SCREEN_I_WINDOW_CONTROLLER_HPP
#define SCREEN_I_WINDOW_CONTROLLER_HPP

#include <windows.h>

namespace screen
{
	class IKeyboardController;
	class IMenuController;

	class IWindowController
	{
	public:
		explicit IWindowController(IMenuController* menuController = nullptr)
			: m_menuController(menuController)
		{
		}

		virtual ~IWindowController() = default;

		virtual void update() = 0;
		virtual void onPaint(HDC deviceContext) = 0;
		virtual void onDestroy() = 0;

		virtual void onReset() {}

		virtual IKeyboardController* getKeyboardController() const { return nullptr; }

		IMenuController* getMenuController() const { return m_menuController; }

	private:
		IMenuController* m_menuController;
	};
}

#endif // SCREEN_I_WINDOW_CONTROLLER_HPP
