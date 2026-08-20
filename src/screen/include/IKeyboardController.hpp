#ifndef SCREEN_I_KEYBOARD_CONTROLLER_HPP
#define SCREEN_I_KEYBOARD_CONTROLLER_HPP

namespace screen
{
	class IKeyboardController
	{
	public:
		enum KeyId
		{
			KeyA,
			KeyB,
			KeyC,
			KeyD,
			KeyE,
			KeyF,
			KeyG,
			KeyH,
			KeyI,
			KeyJ,
			KeyK,
			KeyL,
			KeyM,
			KeyN,
			KeyO,
			KeyP,
			KeyQ,
			KeyR,
			KeyS,
			KeyT,
			KeyU,
			KeyV,
			KeyW,
			KeyX,
			KeyY,
			KeyZ,
			Digit0,
			Digit1,
			Digit2,
			Digit3,
			Digit4,
			Digit5,
			Digit6,
			Digit7,
			Digit8,
			Digit9,
			ArrowUp,
			ArrowDown,
			ArrowLeft,
			ArrowRight,
			Escape,
			Enter,
			Space,
			Tab,
			Backspace,
			Delete,
			Shift,
			Ctrl,
			Alt,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			KeyCount
		};

		virtual ~IKeyboardController() = default;

		virtual void onKeyA() {}
		virtual void onKeyB() {}
		virtual void onKeyC() {}
		virtual void onKeyD() {}
		virtual void onKeyE() {}
		virtual void onKeyF() {}
		virtual void onKeyG() {}
		virtual void onKeyH() {}
		virtual void onKeyI() {}
		virtual void onKeyJ() {}
		virtual void onKeyK() {}
		virtual void onKeyL() {}
		virtual void onKeyM() {}
		virtual void onKeyN() {}
		virtual void onKeyO() {}
		virtual void onKeyP() {}
		virtual void onKeyQ() {}
		virtual void onKeyR() {}
		virtual void onKeyS() {}
		virtual void onKeyT() {}
		virtual void onKeyU() {}
		virtual void onKeyV() {}
		virtual void onKeyW() {}
		virtual void onKeyX() {}
		virtual void onKeyY() {}
		virtual void onKeyZ() {}
		virtual void onDigit0() {}
		virtual void onDigit1() {}
		virtual void onDigit2() {}
		virtual void onDigit3() {}
		virtual void onDigit4() {}
		virtual void onDigit5() {}
		virtual void onDigit6() {}
		virtual void onDigit7() {}
		virtual void onDigit8() {}
		virtual void onDigit9() {}
		virtual void onArrowUp() {}
		virtual void onArrowDown() {}
		virtual void onArrowLeft() {}
		virtual void onArrowRight() {}
		virtual void onEscape() {}
		virtual void onEnter() {}
		virtual void onSpace() {}
		virtual void onTab() {}
		virtual void onBackspace() {}
		virtual void onDelete() {}
		virtual void onShift() {}
		virtual void onCtrl() {}
		virtual void onAlt() {}
		virtual void onF1() {}
		virtual void onF2() {}
		virtual void onF3() {}
		virtual void onF4() {}
		virtual void onF5() {}
		virtual void onF6() {}
		virtual void onF7() {}
		virtual void onF8() {}
		virtual void onF9() {}
		virtual void onF10() {}
		virtual void onF11() {}
		virtual void onF12() {}
	};
}

#endif // SCREEN_I_KEYBOARD_CONTROLLER_HPP
