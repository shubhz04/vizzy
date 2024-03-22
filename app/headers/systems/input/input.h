#pragma once
namespace Vizzy
{
	
	class Mouse {
	
	public:
		enum Button { Left, Right };

		static long appHWND;
		static int x,y;

		static bool isLMB_Down, isLMB_Pressed,isLMB_Up;
		static bool isRMB_Down,isRMB_Pressed,isRMB_Up;

		static void initialize(long _hwnd);
		static void dispose();

		static void process_events();
		static bool is_button_down(Button _button);
		static bool is_button_held(Button _button);
		static bool is_button_up(Button _button);
	};
	class Keyboard {};
}

//Mouse::is_button_down(Mouse::Buttons::Left)