/*
* this header contains all the functions needed for manipulating dwm 
  to send the window back and forth 
*/
#pragma once
namespace Vizzy {
	class DWM {
	public:

		static long WALLPAPER_WORKERW_HWND;
		static long SHELLDLL_WORKERW_HWND;
		static long SHELLDLL_HWND;
		static long SHELLDLL_LISTVIEW_HWND;

		// Initializes all the necessary handles 
		static void initialize();
		//gets the workerw hwnd which handles wallpaper transitions
		static long get_workerw_hwnd();

		// Prints all HWND data to the console
		static void log_hwnds();
	
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