#include "Window.hpp"
#include "IKeyboardController.hpp"
#include "IMenuController.hpp"

namespace screen
{
	namespace
	{
		const wchar_t* WINDOW_CLASS_NAME = L"GameEngineWindowClass";
		const wchar_t* SUB_WINDOW_CLASS_NAME = L"GameEngineSubWindowClass";
		const int SUB_WINDOW_EXIT_BUTTON_ID = 1;
		const int OPTIONS_CURSOR_GAME_RADIO_ID = 2;

		HMENU createMenuBar(IMenuController& menuController)
		{
			HMENU menuBar = CreateMenu();
			bool hasAnyMenu = false;

			HMENU fileMenu = CreatePopupMenu();
			bool hasFileMenu = false;
			if (menuController.isImplemented(IMenuController::FileNew))
			{
				AppendMenu(fileMenu, MF_STRING, Window::MENU_ID_FILE_NEW, L"New");
				hasFileMenu = true;
			}
			if (menuController.isImplemented(IMenuController::FileExit))
			{
				AppendMenu(fileMenu, MF_STRING, Window::MENU_ID_FILE_EXIT, L"Exit");
				hasFileMenu = true;
			}
			if (hasFileMenu)
			{
				AppendMenu(menuBar, MF_POPUP, reinterpret_cast<UINT_PTR>(fileMenu), L"File");
				hasAnyMenu = true;
			}
			else
			{
				DestroyMenu(fileMenu);
			}

			HMENU editMenu = CreatePopupMenu();
			if (menuController.isImplemented(IMenuController::EditOption))
			{
				AppendMenu(editMenu, MF_STRING, Window::MENU_ID_EDIT_OPTION, L"Option");
				AppendMenu(menuBar, MF_POPUP, reinterpret_cast<UINT_PTR>(editMenu), L"Edit");
				hasAnyMenu = true;
			}
			else
			{
				DestroyMenu(editMenu);
			}

			HMENU helpMenu = CreatePopupMenu();
			if (menuController.isImplemented(IMenuController::HelpAbout))
			{
				AppendMenu(helpMenu, MF_STRING, Window::MENU_ID_HELP_ABOUT, L"About");
				AppendMenu(menuBar, MF_POPUP, reinterpret_cast<UINT_PTR>(helpMenu), L"Help");
				hasAnyMenu = true;
			}
			else
			{
				DestroyMenu(helpMenu);
			}

			if (!hasAnyMenu)
			{
				DestroyMenu(menuBar);
				return nullptr;
			}

			return menuBar;
		}

		static LRESULT CALLBACK SubWinProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_COMMAND:
				if (LOWORD(wParam) == SUB_WINDOW_EXIT_BUTTON_ID)
				{
					DestroyWindow(windowHandle);
				}
				return 0;
			default:
				return DefWindowProc(windowHandle, message, wParam, lParam);
			}
		}

		HWND createSubWindowShell(HINSTANCE instance, HWND parent, const wchar_t* title, int width, int height)
		{
			WNDCLASSEX subWindowClass = {};
			subWindowClass.cbSize = sizeof(WNDCLASSEX);
			subWindowClass.style = CS_HREDRAW | CS_VREDRAW;
			subWindowClass.lpfnWndProc = SubWinProc;
			subWindowClass.hInstance = instance;
			subWindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
			subWindowClass.lpszClassName = SUB_WINDOW_CLASS_NAME;

			RegisterClassEx(&subWindowClass);

			return CreateWindowEx(
				0,
				SUB_WINDOW_CLASS_NAME,
				title,
				WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
				CW_USEDEFAULT, CW_USEDEFAULT,
				width, height,
				parent,
				nullptr,
				instance,
				nullptr);
		}

		void addExitButton(HWND subWindowHandle, HINSTANCE instance, int top)
		{
			CreateWindowEx(
				0,
				L"BUTTON",
				L"Exit",
				WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
				100, top, 100, 30,
				subWindowHandle,
				reinterpret_cast<HMENU>(static_cast<INT_PTR>(SUB_WINDOW_EXIT_BUTTON_ID)),
				instance,
				nullptr);
		}

		static LRESULT CALLBACK WinProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
		{
			if (message == WM_NCCREATE)
			{
				CREATESTRUCT* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
				SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
				return DefWindowProc(windowHandle, message, wParam, lParam);
			}

			Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));

			switch (message)
			{
			case WM_PAINT:
			{
				PAINTSTRUCT paintStruct;
				HDC deviceContext = BeginPaint(windowHandle, &paintStruct);
				FillRect(deviceContext, &paintStruct.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

				if (window != nullptr)
				{
					window->getController().onPaint(deviceContext);
				}

				EndPaint(windowHandle, &paintStruct);
				return 0;
			}
			case WM_KEYDOWN:
				if (window != nullptr)
				{
					IKeyboardController* keyboardController = window->getController().getKeyboardController();
					if (keyboardController != nullptr)
					{
						bool keyHandled = true;
						switch (wParam)
						{
						case VK_UP:
							keyboardController->onArrowUp();
							break;
						case VK_DOWN:
							keyboardController->onArrowDown();
							break;
						case VK_LEFT:
							keyboardController->onArrowLeft();
							break;
						case VK_RIGHT:
							keyboardController->onArrowRight();
							break;
						default:
							keyHandled = false;
							break;
						}

						if (keyHandled)
						{
							InvalidateRect(windowHandle, nullptr, TRUE);
						}
					}
				}
				return 0;
			case WM_COMMAND:
				if (window != nullptr)
				{
					IMenuController* menuController = window->getController().getMenuController();
					if (menuController != nullptr)
					{
						switch (LOWORD(wParam))
						{
						case Window::MENU_ID_FILE_NEW:
							menuController->onFileNew();
							InvalidateRect(windowHandle, nullptr, TRUE);
							break;
						case Window::MENU_ID_FILE_EXIT:
							menuController->onFileExit();
							break;
						case Window::MENU_ID_EDIT_OPTION:
							menuController->onEditOption();
							break;
						case Window::MENU_ID_HELP_ABOUT:
							menuController->onHelpAbout();
							break;
						default:
							break;
						}
					}
				}
				return 0;
			case WM_DESTROY:
				if (window != nullptr)
				{
					window->getController().onDestroy();
				}
				PostQuitMessage(0);
				return 0;
			default:
				return DefWindowProc(windowHandle, message, wParam, lParam);
			}
		}
	}

	Window::Window(IWindowController& controller)
		: m_controller(controller)
		, m_windowHandle(nullptr)
		, m_instance(nullptr)
	{
	}

	IWindowController& Window::getController()
	{
		return m_controller;
	}

	HWND Window::create(HINSTANCE instance, int showCommand)
	{
		m_instance = instance;

		WNDCLASSEX windowClass = {};
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = WinProc;
		windowClass.hInstance = instance;
		windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		windowClass.lpszClassName = WINDOW_CLASS_NAME;

		RegisterClassEx(&windowClass);

		HMENU menuBar = nullptr;
		IMenuController* menuController = m_controller.getMenuController();
		if (menuController != nullptr)
		{
			menuBar = createMenuBar(*menuController);
		}

		m_windowHandle = CreateWindowEx(
			0,
			WINDOW_CLASS_NAME,
			L"Game Engine",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			DEFAULT_WIDTH, DEFAULT_HEIGHT,
			nullptr,
			menuBar,
			instance,
			this);

		if (m_windowHandle != nullptr)
		{
			ShowWindow(m_windowHandle, showCommand);
		}

		return m_windowHandle;
	}

	int Window::runMessageLoop()
	{
		MSG message = {};
		while (GetMessage(&message, nullptr, 0, 0))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		return static_cast<int>(message.wParam);
	}

	void Window::close()
	{
		if (m_windowHandle != nullptr)
		{
			DestroyWindow(m_windowHandle);
		}
	}

	HWND Window::openSubWindow(const wchar_t* title)
	{
		HWND subWindowHandle = createSubWindowShell(m_instance, m_windowHandle, title, 300, 150);

		if (subWindowHandle != nullptr)
		{
			addExitButton(subWindowHandle, m_instance, 50);
			ShowWindow(subWindowHandle, SW_SHOW);
		}

		return subWindowHandle;
	}

	HWND Window::openOptionsWindow()
	{
		HWND subWindowHandle = createSubWindowShell(m_instance, m_windowHandle, L"Options", 300, 170);

		if (subWindowHandle != nullptr)
		{
			CreateWindowEx(
				0,
				L"BUTTON",
				L"Tutorial_Basic",
				WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
				10, 10, 270, 50,
				subWindowHandle,
				nullptr,
				m_instance,
				nullptr);

			HWND cursorGameRadio = CreateWindowEx(
				0,
				L"BUTTON",
				L"Cursor Game",
				WS_VISIBLE | WS_CHILD | WS_GROUP | BS_AUTORADIOBUTTON,
				20, 30, 200, 20,
				subWindowHandle,
				reinterpret_cast<HMENU>(static_cast<INT_PTR>(OPTIONS_CURSOR_GAME_RADIO_ID)),
				m_instance,
				nullptr);

			if (cursorGameRadio != nullptr)
			{
				SendMessage(cursorGameRadio, BM_SETCHECK, BST_CHECKED, 0);
			}

			addExitButton(subWindowHandle, m_instance, 110);
			ShowWindow(subWindowHandle, SW_SHOW);
		}

		return subWindowHandle;
	}
}
