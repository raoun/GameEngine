#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Window.hpp"
#include "IKeyboardController.hpp"
#include "IMenuController.hpp"
#include <windows.h>

namespace
{
	class MockKeyboardController : public screen::IKeyboardController
	{
	public:
		MOCK_METHOD(void, onArrowUp, (), (override));
		MOCK_METHOD(void, onArrowDown, (), (override));
		MOCK_METHOD(void, onArrowLeft, (), (override));
		MOCK_METHOD(void, onArrowRight, (), (override));
	};

	class MockControllerWithKeyboard : public screen::IWindowController
	{
	public:
		explicit MockControllerWithKeyboard(screen::IKeyboardController& keyboardController)
			: screen::IWindowController(nullptr)
			, m_keyboardController(keyboardController)
		{
		}

		MOCK_METHOD(void, update, (), (override));
		MOCK_METHOD(void, onPaint, (HDC), (override));
		MOCK_METHOD(void, onDestroy, (), (override));

		screen::IKeyboardController* getKeyboardController() const override { return &m_keyboardController; }

	private:
		screen::IKeyboardController& m_keyboardController;
	};

	class MockController : public screen::IWindowController, public screen::IMenuController
	{
	public:
		MockController() : screen::IWindowController(this) {}

		MOCK_METHOD(void, update, (), (override));
		MOCK_METHOD(void, onPaint, (HDC), (override));
		MOCK_METHOD(void, onDestroy, (), (override));
		MOCK_METHOD(void, onFileNew, (), (override));
		MOCK_METHOD(void, onFileExit, (), (override));
		MOCK_METHOD(void, onEditOption, (), (override));
		MOCK_METHOD(void, onHelpAbout, (), (override));
	};

	class NoMenuController : public screen::IWindowController
	{
	public:
		NoMenuController() : screen::IWindowController(nullptr) {}
		void update() override {}
		void onPaint(HDC) override {}
		void onDestroy() override {}
	};

	class PartialMenuController : public screen::IWindowController, public screen::IMenuController
	{
	public:
		PartialMenuController() : screen::IWindowController(this)
		{
			markImplemented(HelpAbout);
		}
		void update() override {}
		void onPaint(HDC) override {}
		void onDestroy() override {}
	};

	class FullMenuController : public screen::IWindowController, public screen::IMenuController
	{
	public:
		FullMenuController() : screen::IWindowController(this)
		{
			markImplemented(FileNew);
			markImplemented(FileExit);
			markImplemented(EditOption);
			markImplemented(HelpAbout);
		}
		void update() override {}
		void onPaint(HDC) override {}
		void onDestroy() override {}
	};
}

TEST(WindowTest, PaintMessageCallsControllerOnPaint)
{
	testing::NiceMock<MockController> controller;
	screen::Window window(controller);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	EXPECT_CALL(controller, onPaint(testing::_)).Times(1);

	SendMessage(windowHandle, WM_PAINT, 0, 0);

	DestroyWindow(windowHandle);
}

TEST(WindowTest, DestroyingWindowCallsControllerOnDestroy)
{
	testing::NiceMock<MockController> controller;
	screen::Window window(controller);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	EXPECT_CALL(controller, onDestroy()).Times(1);

	DestroyWindow(windowHandle);
}

TEST(WindowTest, FileNewMenuCommandCallsControllerOnFileNew)
{
	testing::NiceMock<MockController> controller;
	screen::Window window(controller);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	EXPECT_CALL(controller, onFileNew()).Times(1);

	SendMessage(windowHandle, WM_COMMAND, MAKEWPARAM(screen::Window::MENU_ID_FILE_NEW, 0), 0);

	DestroyWindow(windowHandle);
}

TEST(WindowTest, FileExitMenuCommandCallsControllerOnFileExit)
{
	testing::NiceMock<MockController> controller;
	screen::Window window(controller);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	EXPECT_CALL(controller, onFileExit()).Times(1);

	SendMessage(windowHandle, WM_COMMAND, MAKEWPARAM(screen::Window::MENU_ID_FILE_EXIT, 0), 0);

	DestroyWindow(windowHandle);
}

TEST(WindowTest, EditOptionMenuCommandCallsControllerOnEditOption)
{
	testing::NiceMock<MockController> controller;
	screen::Window window(controller);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	EXPECT_CALL(controller, onEditOption()).Times(1);

	SendMessage(windowHandle, WM_COMMAND, MAKEWPARAM(screen::Window::MENU_ID_EDIT_OPTION, 0), 0);

	DestroyWindow(windowHandle);
}

TEST(WindowTest, HelpAboutMenuCommandCallsControllerOnHelpAbout)
{
	testing::NiceMock<MockController> controller;
	screen::Window window(controller);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	EXPECT_CALL(controller, onHelpAbout()).Times(1);

	SendMessage(windowHandle, WM_COMMAND, MAKEWPARAM(screen::Window::MENU_ID_HELP_ABOUT, 0), 0);

	DestroyWindow(windowHandle);
}

TEST(WindowTest, ArrowKeyDownCallsKeyboardControllerOnArrowRight)
{
	testing::NiceMock<MockKeyboardController> keyboardController;
	testing::NiceMock<MockControllerWithKeyboard> controller(keyboardController);
	screen::Window window(controller);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	EXPECT_CALL(keyboardController, onArrowRight()).Times(1);

	SendMessage(windowHandle, WM_KEYDOWN, VK_RIGHT, 0);

	DestroyWindow(windowHandle);
}

TEST(WindowTest, NoKeyboardControllerDoesNotThrowOnArrowKey)
{
	testing::NiceMock<MockController> controller;
	screen::Window window(controller);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	EXPECT_NO_THROW(SendMessage(windowHandle, WM_KEYDOWN, VK_RIGHT, 0));

	DestroyWindow(windowHandle);
}

TEST(WindowTest, OpenSubWindowCreatesVisibleWindow)
{
	testing::NiceMock<MockController> controller;
	screen::Window window(controller);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	HWND subWindowHandle = window.openSubWindow(L"About");
	ASSERT_NE(subWindowHandle, nullptr);
	EXPECT_TRUE(IsWindow(subWindowHandle));

	DestroyWindow(subWindowHandle);
	DestroyWindow(windowHandle);
}

TEST(WindowTest, NoMenuControllerResultsInNoMenuBar)
{
	NoMenuController controller;
	screen::Window window(controller);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	EXPECT_EQ(GetMenu(windowHandle), nullptr);

	DestroyWindow(windowHandle);
}

TEST(WindowTest, PartialMenuControllerOnlyAddsTheImplementedTopLevelMenu)
{
	PartialMenuController controller;
	screen::Window window(controller);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	HMENU menuBar = GetMenu(windowHandle);
	ASSERT_NE(menuBar, nullptr);
	EXPECT_EQ(GetMenuItemCount(menuBar), 1);

	wchar_t label[16] = {};
	GetMenuString(menuBar, 0, label, ARRAYSIZE(label), MF_BYPOSITION);
	EXPECT_STREQ(label, L"Help");

	DestroyWindow(windowHandle);
}

TEST(WindowTest, FullyImplementedControllerAddsAllThreeTopLevelMenus)
{
	FullMenuController controller;
	screen::Window window(controller);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	HMENU menuBar = GetMenu(windowHandle);
	ASSERT_NE(menuBar, nullptr);
	EXPECT_EQ(GetMenuItemCount(menuBar), 3);

	DestroyWindow(windowHandle);
}
