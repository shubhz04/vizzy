/*
* this header contains all the functions needed for manipulating dwm
  to send the window back and forth
*/
#pragma once
#include <vector>
#include <string>
namespace Vizzy {
	class DWM {
	public:
		struct VZ_RECT {
			int x, y;
			int width, height;

			VZ_RECT() { x = y = width = height = 0; };
			VZ_RECT(int _x, int _y, int _width, int _height) {
				x = _x; y = _y;
				width = _width;
				height = _height;
			}
		};
		struct VZ_WINDOW {
			std::string name;
			VZ_RECT rect;

			VZ_WINDOW(std::string _name, VZ_RECT _rect) {
				name = _name;
				rect = _rect;
			}
		};

		static long WALLPAPER_WORKERW_HWND;
		static long SHELLDLL_WORKERW_HWND;
		static long SHELLDLL_HWND;
		static long SHELLDLL_LISTVIEW_HWND;

		static std::vector<VZ_WINDOW> activeWindowList;
		// Initializes all the necessary handles 
		static void initialize();


		// Prints all HWND data to the console
		static void log_hwnds();

		// Gets all user desktop windows rect and names
		// Ignores system default windows which aren't visible
		static bool query_active_windows();

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