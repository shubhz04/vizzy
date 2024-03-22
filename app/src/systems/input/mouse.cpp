#include "../../../headers/systems/input/input.h"
#include <Windows.h>
#include <iostream>
using namespace Vizzy;

long Mouse::appHWND;
int Mouse::x, Mouse::y;

bool Mouse::isLMB_Down, Mouse::isLMB_Pressed, Mouse::isLMB_Up;
bool Mouse::isRMB_Down, Mouse::isRMB_Pressed, Mouse::isRMB_Up;

MSG msg;
HHOOK hhk_LLMouse;
POINT mouseCoords;

static LRESULT CALLBACK LL_MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	//Checks both Client and Non-client area
	//Events happened
	if (nCode >= 0) {

		if (wParam == WM_LBUTTONDOWN || wParam == WM_NCLBUTTONDOWN) {

		}

		if (wParam == WM_RBUTTONDOWN || wParam == WM_NCLBUTTONDOWN) {

		}
	}
	return  CallNextHookEx(0, nCode, wParam, lParam);
}

#pragma region CoreEvents

void Vizzy::Mouse::initialize(long _hwnd)
{
	appHWND = _hwnd;
	hhk_LLMouse = SetWindowsHookEx(WH_MOUSE_LL, LL_MouseProc, 0, 0);
}
void Vizzy::Mouse::dispose()
{
	UnhookWindowsHookEx(hhk_LLMouse);
}

void Mouse::process_events() {
	//retrieves current mouse position
	if (GetCursorPos(&mouseCoords)) {
		x = mouseCoords.x;
		y = mouseCoords.y;
	};

	//peeks in the queue to get if any MOUSE Events like click happened;
	if (PeekMessageA(&msg,(HWND)appHWND, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	

}
#pragma endregion
#pragma region CustomEvents
bool Mouse::is_button_down(Button _button) {
	if (_button == Button::Left) { return isLMB_Down; }
	if (_button == Button::Right) { return isRMB_Down; }
}

bool Mouse::is_button_held(Button _button) {
	if (_button == Button::Left) { return isLMB_Pressed; }
	if (_button == Button::Right) { return isRMB_Pressed; }
}

bool Mouse::is_button_up(Button _button) {
	if (_button == Button::Left) { return isLMB_Up; }
	if (_button == Button::Right) { return isRMB_Up; }
}
#pragma endregion
