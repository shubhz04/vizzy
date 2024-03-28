#include "../../headers/utility/dwm.h"
#include "../../headers/utility/debug.h"
#include <Windows.h>
#include "../../headers/systems/devices/display.h"

using namespace Vizzy;

long DWM::WALLPAPER_WORKERW_HWND;
long DWM::SHELLDLL_WORKERW_HWND;
long DWM::SHELLDLL_HWND;
long DWM::SHELLDLL_LISTVIEW_HWND;

std::vector<VZ_WINDOW> DWM::activeWindowList;
std::vector<VZ_POINT> DWM::samplePoints;


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

	// Min left and top coords for discarding as minimized window
	const int WIN_MIN_COORDS = -15000;
	// Return if window is minimized
	if (winRect.left < WIN_MIN_COORDS
		|| winRect.top < WIN_MIN_COORDS
		|| winRect.right < WIN_MIN_COORDS
		|| winRect.bottom < WIN_MIN_COORDS)
		return TRUE;

	// Otherwise 
	// Convert title to a string from wstring
	std::string winTitle(title.begin(), title.end());

	// Creates a final VZ_RECT from RECT 
	VZ_RECT finalWinRect(
		winRect.left,
		winRect.top,
		winRect.right,
		winRect.bottom
	);

	// Creates a VZ_WINDOW for storing the data and pushes it in the active windows vector.
	VZ_WINDOW finalWin(winTitle, (long)hwnd, finalWinRect);
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
	// Resets the existing vector
	activeWindowList.clear();

	// Enumerates all windows based on some conditions.
	EnumWindows(GET_WINDOWS_PROC, 0);

	// If atleast 1 windows found successfull
	// otherwise return failed response.
	if (activeWindowList.size() > 0)
		return true;
	else
		return false;
}

bool Vizzy::DWM::is_desktop_obscured(std::vector<VZ_POINT> _queryPoints, std::vector<VZ_WINDOW> _activeWindows)
{
	std::vector<bool> result(_queryPoints.size());

	for (int i = 0; i < _queryPoints.size(); i++)
	{
		VZ_POINT point = _queryPoints[i];
		for (auto& window : _activeWindows) {

			if (Vizzy::is_point_in_rect(point, window.rect)) {

				result[i] = true;
			}
		}
	}

	for (const bool& i : result) {
		if (i == false) {
			return false;
		}
	}
	return true;
}

void Vizzy::DWM::configure_sample_points(int _padding, int _rows, int _columns)
{


	int minX = _padding, maxX = Display::width - _padding;

	int minY = _padding, maxY = Display::height - _padding;

	int xGap = (Display::width - (2* _padding)) / _columns;
	int yGap = (Display::height - (2 * _padding)) / _rows;

	for (int i = 0; i < _columns; i++)
	{
		for (int j = 0; j < _rows; j++)
		{
			DWM::samplePoints.push_back(VZ_POINT(2 *minX + i * xGap, minY + j * yGap));
		}
	}
}

bool Vizzy::is_point_in_rect(VZ_POINT _point, VZ_RECT _rect)
{
	return ((_point.x > _rect.left) && (_point.x < _rect.right) && (_point.y > _rect.top) && (_point.y < _rect.bottom));
}

