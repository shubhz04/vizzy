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

		VZ_WINDOW(std::string _name,long _hwnd, VZ_RECT _rect) {
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
		// ----------- HWNDS -------------
		static long WALLPAPER_WORKERW_HWND;
		static long SHELLDLL_HWND;
		static long SHELLDLL_LISTVIEW_HWND;
		static long SHELLDLL_WORKERW_HWND;
		// -------------------------------


		// List of active windows in desktop.
		static std::vector<VZ_WINDOW> activeWindowList;
		// List of points used for checking desktop is obscured or not.
		static std::vector<VZ_POINT> samplePoints;

		// Initializes all the necessary handles 
		static void initialize();

		static void log_hwnds();

		// Gets all user desktop windows rect and names
		// Ignores system default windows which aren't visible
		static bool query_active_windows();

		// Sets up sample points 
		static void configure_sample_points(int _padding, int _rows, int _columns);
		static bool is_desktop_obscured(std::vector<VZ_POINT> _queryPoints, std::vector<VZ_WINDOW> _activeWindows);

		
	};


}


/*



//sends a window to the background of the icons view as a child
	static void send_to_desktop(long _hwnd);

	//checks if the desktop is obscured or not, to enable and pause playback
	static bool is_desktop_obscured();

	static bool is_shellview_focused();

	static bool is_shell_workerw_focused();






*/