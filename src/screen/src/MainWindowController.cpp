#include "MainWindowController.hpp"
#include "Window.hpp"

namespace screen
{
	MainWindowController::MainWindowController()
		: IWindowController(this)
		, m_window(nullptr)
		, m_activeGame(nullptr)
	{
		markImplemented(FileNew);
		markImplemented(FileExit);
		markImplemented(EditOption);
		markImplemented(HelpAbout);
	}

	MainWindowController::~MainWindowController()
	{
	}

	void MainWindowController::setWindow(Window& window)
	{
		m_window = &window;
	}

	void MainWindowController::setActiveGame(IWindowController& activeGame)
	{
		m_activeGame = &activeGame;
	}

	void MainWindowController::update()
	{
		if (m_activeGame != nullptr)
		{
			m_activeGame->update();
		}
	}

	void MainWindowController::onPaint(HDC deviceContext)
	{
		if (m_activeGame != nullptr)
		{
			m_activeGame->onPaint(deviceContext);
		}
	}

	void MainWindowController::onDestroy()
	{
		if (m_activeGame != nullptr)
		{
			m_activeGame->onDestroy();
		}
	}

	IKeyboardController* MainWindowController::getKeyboardController() const
	{
		return m_activeGame != nullptr ? m_activeGame->getKeyboardController() : nullptr;
	}

	void MainWindowController::onFileNew()
	{
		if (m_activeGame != nullptr)
		{
			m_activeGame->onReset();
		}
	}

	void MainWindowController::onFileExit()
	{
		if (m_window != nullptr)
		{
			m_window->close();
		}
	}

	void MainWindowController::onEditOption()
	{
		if (m_window != nullptr)
		{
			m_window->openOptionsWindow();
		}
	}

	void MainWindowController::onHelpAbout()
	{
		if (m_window != nullptr)
		{
			m_window->openSubWindow(L"About");
		}
	}
}
