/*
* this header contains all the functions needed for manipulating dwm
  to send the window back and forth
*/
#pragma once
#include <vector>
#include <string>
namespace Vizzy {

	// Contains data structure and utility for lightweight cross header reference without windef
#pragma region Data-Structures

	// An arbitary screen point with X & Y coords.
	struct VZ_POINT {
		int x, y;

		VZ_POINT() { x = y = 0; };
		VZ_POINT(int _x, int _y) { x = _x; y = _y; };
	};

	// A rect containing window size and position 
	struct VZ_RECT {
		int left, right;
		int top, bottom;

		VZ_RECT() { left = top = right = bottom = 0; };
		VZ_RECT(int _left, int _top, int _right, int _bottom) {
			left = _left;
			top = _top;
			right = _right;
			bottom = _bottom;
		}
	};

	// Represents a window with a title , rect and a hwnd
	struct VZ_WINDOW {
		std::string name;
		long hwnd;
		VZ_RECT rect;

		VZ_WINDOW(std::string _name, long _hwnd, VZ_RECT _rect) {
			name = _name;
			hwnd = _hwnd;
			rect = _rect;
		}
	};

#pragma endregion
#pragma region Utility Func
	static bool is_point_in_rect(VZ_POINT _point, VZ_RECT _rect);
#pragma endregion

	class DWM {
	public:
		// Consts
		const static int DWM_UPDATE_INTERVAL = 500;


		// ----------- HWNDS -------------
		static long APP_HWND;
		static long WALLPAPER_WORKERW_HWND;
		static long SHELLDLL_HWND;
		static long SHELLDLL_LISTVIEW_HWND;
		static long SHELLDLL_WORKERW_HWND;
		// -------------------------------


		static bool isFocused;
		static bool isShellFocused;

		// List of active windows in desktop.
		static std::vector<VZ_WINDOW> activeWindowList;
		// List of points used for checking desktop is obscured or not.
		static std::vector<VZ_POINT> samplePoints;

		// Initializes all the necessary handles 
		static void initialize(long _hwnd);

		static void log_hwnds();

		// Gets all user desktop windows rect and names
		// Ignores some windows based on a exclusion rule
		static bool query_active_windows();

		// Sets up sample points 
		static void configure_sample_points(int _padding, int _rows, int _columns);

		// Checks if the desktop is obscured based on some dataset
		static bool is_desktop_obscured(std::vector<VZ_POINT> _queryPoints, std::vector<VZ_WINDOW> _activeWindows);

		// Runs a loop on seperate thread to continously check for desktop obscuration every n interval.
		static void dwm_loopback();

	};


}

