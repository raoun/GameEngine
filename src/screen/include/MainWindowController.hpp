#ifndef SCREEN_MAIN_WINDOW_CONTROLLER_HPP
#define SCREEN_MAIN_WINDOW_CONTROLLER_HPP

#include "IMenuController.hpp"
#include "IWindowController.hpp"

namespace screen
{
	class IKeyboardController;
	class Window;

	class MainWindowController : public IWindowController, public IMenuController
	{
	public:
		MainWindowController();
		~MainWindowController() override;

		void setWindow(Window& window);
		void setActiveGame(IWindowController& activeGame);

		void update() override;
		void onPaint(HDC deviceContext) override;
		void onDestroy() override;

		IKeyboardController* getKeyboardController() const override;

		void onFileNew() override;
		void onFileExit() override;
		void onEditOption() override;
		void onHelpAbout() override;

	private:
		Window* m_window;
		IWindowController* m_activeGame;
	};
}

#endif // SCREEN_MAIN_WINDOW_CONTROLLER_HPP
