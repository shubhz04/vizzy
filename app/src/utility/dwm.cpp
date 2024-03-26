#include "../../headers/utility/dwm.h"
#include "../../headers/utility/debug.h"
#include <Windows.h>

using namespace Vizzy;

long DWM::WALLPAPER_WORKERW_HWND;
long DWM::SHELLDLL_WORKERW_HWND;
long DWM::SHELLDLL_HWND;
long DWM::SHELLDLL_LISTVIEW_HWND;

std::vector<DWM::VZ_WINDOW> DWM::activeWindowList;

// Sets the default HWND's for the desktop handles
BOOL CALLBACK INIT_WINDOWS_PROC(HWND _hwnd, LPARAM _lParam)
{
	HWND shellDLL_hwnd = FindWindowEx(_hwnd, NULL, L"SHELLDLL_DefView", NULL);
	HWND* ret = (HWND*)_lParam;

	if (shellDLL_hwnd)
	{
		// Succesfully found the first WorkerW containing the SHELLDLL 
		DWM::SHELLDLL_WORKERW_HWND = (long)_hwnd;
		DWM::SHELLDLL_HWND = (long)shellDLL_hwnd;

		// Find the first child i.e. the listview containing the desktop icons.
		DWM::SHELLDLL_LISTVIEW_HWND = (long)FindWindowEx(shellDLL_hwnd, NULL, L"SysListView32", NULL);;
		
		// Gets the WorkerW Window after the current WorkerW .
		*ret = FindWindowEx(NULL, _hwnd, L"WorkerW", NULL);
	}
	return true;
}

// Gets all active windows of the desktop (both minimized and onscreen)
BOOL CALLBACK GET_WINDOWS_PROC(HWND hwnd, LPARAM lParam) {

	WCHAR windowTitle[1024];
	int length = ::GetWindowTextLength(hwnd);

	// Gets window title
	GetWindowTextW(hwnd, windowTitle, 1024);
	std::wstring title(&windowTitle[0]);

	// Return if window is not visible or is in exclusion list
	if (!IsWindowVisible(hwnd)
		|| length == 0
		|| title == L"Program Manager"
		|| title == L"Windows Input Experience")
		return TRUE;

	// Otherwise continue extracting data from the rect
	RECT winRect;
	GetWindowRect(hwnd, &winRect);

	// Convert title to a string from wstring
	std::string winTitle(title.begin(), title.end());

	// Prints the data for now
	Debug::log(winTitle, " ||  DIMENSION ARE ", winRect.left, " ", winRect.top, " ", winRect.right, " ", winRect.bottom);

	// Creates a final VZ_RECT from RECT type for cross header access
	// without including windef .
	DWM::VZ_RECT finalWinRect(
		winRect.left,
		winRect.top,
		winRect.right,
		winRect.bottom
	);

	// Creates a VZ_WINDOW for storing the data and pushes it in the active windows vector.
	DWM::VZ_WINDOW finalWin(winTitle, finalWinRect);
	DWM::activeWindowList.push_back(finalWin);

	return TRUE;
}


void DWM::initialize()
{
	// Fetch the Progman window
	HWND progman = FindWindow(L"ProgMan", NULL);
	// Send 0x052C to Progman. This message directs Progman to spawn a 
	// WorkerW behind the desktop icons. If it is already there, nothing 
	// happens.
	SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);
	// We enumerate all Windows, until we find one, that has the SHELLDLL_DefView 
	// as a child. 
	// If we found that window, we take its next sibling and assign it to workerw.
	HWND wallpaper_workerw_hwnd = nullptr;
	EnumWindows(INIT_WINDOWS_PROC, (LPARAM)&wallpaper_workerw_hwnd);

	DWM::WALLPAPER_WORKERW_HWND = (long)wallpaper_workerw_hwnd;

}

void Vizzy::DWM::log_hwnds()
{
	Debug::log("----- DWM HWNDS ------");;
	Debug::log("WALLWORKER   : ", Vizzy::DWM::WALLPAPER_WORKERW_HWND);
	Debug::log("SHELLDLL     : ", Vizzy::DWM::SHELLDLL_HWND);
	Debug::log("LISTVIEW     : ", Vizzy::DWM::SHELLDLL_LISTVIEW_HWND);
	Debug::log("SHELL WORKER : ", Vizzy::DWM::SHELLDLL_WORKERW_HWND);
	Debug::log("----------------------");;

}

bool Vizzy::DWM::query_active_windows()
{
	// Enumerates all windows based on some conditions.
	EnumWindows(GET_WINDOWS_PROC, 0);

	// If atleast 1 windows found successfull
	// otherwise return failed response.
	if (activeWindowList.size() > 0)
		return true;
	else
		return false;	
}

