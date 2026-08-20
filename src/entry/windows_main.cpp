#include "windows.h"
#include "Window.hpp"
#include "MainWindowController.hpp"
#include "CursorGame.hpp"
#include "CursorGameController.hpp"
#include "CursorKeyboardController.hpp"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int showCommand)
{
    tutorial::basic::cursor::CursorGame cursorGame(screen::Window::DEFAULT_WIDTH, screen::Window::DEFAULT_HEIGHT);
    tutorial::basic::cursor::CursorKeyboardController cursorKeyboardController(cursorGame);
    tutorial::basic::cursor::CursorGameController cursorGameController(cursorGame, cursorKeyboardController);

    screen::MainWindowController controller;
    controller.setActiveGame(cursorGameController);

    screen::Window window(controller);
    controller.setWindow(window);

    if (window.create(instance, showCommand) == nullptr)
    {
        return 0;
    }

    return window.runMessageLoop();
}
