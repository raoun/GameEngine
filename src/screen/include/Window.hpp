#ifndef SCREEN_WINDOW_HPP
#define SCREEN_WINDOW_HPP

#include "IWindowController.hpp"
#include <windows.h>

namespace screen
{
	class Window
	{
	public:
		static constexpr int MENU_ID_FILE_NEW = 1001;
		static constexpr int MENU_ID_FILE_EXIT = 1002;
		static constexpr int MENU_ID_EDIT_OPTION = 1003;
		static constexpr int MENU_ID_HELP_ABOUT = 1004;

		static constexpr int DEFAULT_WIDTH = 1280;
		static constexpr int DEFAULT_HEIGHT = 720;

		explicit Window(IWindowController& controller);

		HWND create(HINSTANCE instance, int showCommand);
		int runMessageLoop();
		void close();
		HWND openSubWindow(const wchar_t* title);
		HWND openOptionsWindow();

		IWindowController& getController();

	private:
		IWindowController& m_controller;
		HWND m_windowHandle;
		HINSTANCE m_instance;
	};
}

#endif // SCREEN_WINDOW_HPP
