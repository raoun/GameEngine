#ifndef SCREEN_I_MOUSE_CONTROLLER_HPP
#define SCREEN_I_MOUSE_CONTROLLER_HPP

namespace screen
{
	struct MousePosition
	{
		int x = 0;
		int y = 0;
	};

	class IMouseController
	{
	public:
		enum MouseButton
		{
			Left,
			Right,
			Middle,
			MouseButtonCount
		};

		virtual ~IMouseController() = default;

		virtual MousePosition getMousePosition() const { return MousePosition(); }
		virtual void buttonClick(MouseButton button) {}
	};
}

#endif // SCREEN_I_MOUSE_CONTROLLER_HPP
