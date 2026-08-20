#include "gtest/gtest.h"
#include "MainWindowController.hpp"
#include "Window.hpp"
#include <windows.h>

namespace
{
	class FakeGame : public screen::IWindowController
	{
	public:
		void update() override {}
		void onPaint(HDC) override {}
		void onDestroy() override {}
		void onReset() override { wasReset = true; }

		bool wasReset = false;
	};
}

TEST(MainWindowControllerTest, OnFileNewResetsTheActiveGame)
{
	screen::MainWindowController controller;
	FakeGame game;
	controller.setActiveGame(game);

	controller.onFileNew();

	EXPECT_TRUE(game.wasReset);
}

TEST(MainWindowControllerTest, LifecycleMethodsDoNotThrow)
{
	screen::MainWindowController controller;

	EXPECT_NO_THROW(controller.update());
	EXPECT_NO_THROW(controller.onPaint(nullptr));
	EXPECT_NO_THROW(controller.onDestroy());
}

TEST(MainWindowControllerTest, MenuHandlersDoNotThrowWithoutAWindow)
{
	screen::MainWindowController controller;

	EXPECT_NO_THROW(controller.onFileNew());
	EXPECT_NO_THROW(controller.onFileExit());
	EXPECT_NO_THROW(controller.onEditOption());
	EXPECT_NO_THROW(controller.onHelpAbout());
}

TEST(MainWindowControllerTest, ImplementsAllFourMenuCommands)
{
	screen::MainWindowController controller;

	EXPECT_TRUE(controller.isImplemented(screen::IMenuController::FileNew));
	EXPECT_TRUE(controller.isImplemented(screen::IMenuController::FileExit));
	EXPECT_TRUE(controller.isImplemented(screen::IMenuController::EditOption));
	EXPECT_TRUE(controller.isImplemented(screen::IMenuController::HelpAbout));
}

TEST(MainWindowControllerTest, ExposesItselfAsItsOwnMenuController)
{
	screen::MainWindowController controller;

	EXPECT_EQ(controller.getMenuController(), static_cast<screen::IMenuController*>(&controller));
}

TEST(MainWindowControllerTest, OnFileExitClosesTheAttachedWindow)
{
	screen::MainWindowController controller;
	screen::Window window(controller);
	controller.setWindow(window);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	controller.onFileExit();

	EXPECT_FALSE(IsWindow(windowHandle));
}

TEST(MainWindowControllerTest, OnHelpAboutOpensASubWindow)
{
	screen::MainWindowController controller;
	screen::Window window(controller);
	controller.setWindow(window);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	controller.onHelpAbout();

	HWND subWindowHandle = FindWindow(nullptr, L"About");
	EXPECT_NE(subWindowHandle, nullptr);

	if (subWindowHandle != nullptr)
	{
		DestroyWindow(subWindowHandle);
	}

	DestroyWindow(windowHandle);
}

TEST(MainWindowControllerTest, OnEditOptionOpensOptionsWindowWithCheckedCursorGameRadio)
{
	screen::MainWindowController controller;
	screen::Window window(controller);
	controller.setWindow(window);

	HWND windowHandle = window.create(GetModuleHandle(nullptr), SW_HIDE);
	ASSERT_NE(windowHandle, nullptr);

	controller.onEditOption();

	HWND optionsWindowHandle = FindWindow(nullptr, L"Options");
	ASSERT_NE(optionsWindowHandle, nullptr);

	HWND groupBox = FindWindowEx(optionsWindowHandle, nullptr, L"BUTTON", L"Tutorial_Basic");
	EXPECT_NE(groupBox, nullptr);

	HWND cursorGameRadio = FindWindowEx(optionsWindowHandle, nullptr, L"BUTTON", L"Cursor Game");
	ASSERT_NE(cursorGameRadio, nullptr);
	EXPECT_EQ(SendMessage(cursorGameRadio, BM_GETCHECK, 0, 0), BST_CHECKED);

	DestroyWindow(optionsWindowHandle);
	DestroyWindow(windowHandle);
}
