#ifndef SCREEN_I_MENU_CONTROLLER_HPP
#define SCREEN_I_MENU_CONTROLLER_HPP

#include <bitset>

namespace screen
{
	class IMenuController
	{
	public:
		enum MenuId
		{
			FileNew,
			FileExit,
			EditOption,
			HelpAbout,
			MenuCount
		};

		virtual ~IMenuController() = default;

		virtual void onFileNew() {}
		virtual void onFileExit() {}
		virtual void onEditOption() {}
		virtual void onHelpAbout() {}

		bool isImplemented(MenuId id) const { return m_implementedMenus.test(id); }

	protected:
		void markImplemented(MenuId id) { m_implementedMenus.set(id); }

	private:
		std::bitset<MenuCount> m_implementedMenus;
	};
}

#endif // SCREEN_I_MENU_CONTROLLER_HPP
