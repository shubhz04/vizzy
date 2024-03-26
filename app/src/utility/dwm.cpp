#include "../../headers/utility/dwm.h"
#include "../../headers/utility/debug.h"
#include <Windows.h>

long Vizzy::DWM::WALLPAPER_WORKERW_HWND;
long Vizzy::DWM::SHELLDLL_WORKERW_HWND;
long Vizzy::DWM::SHELLDLL_HWND;
long Vizzy::DWM::SHELLDLL_LISTVIEW_HWND;


BOOL CALLBACK EnumWindowsProc(HWND _hwnd, LPARAM _lParam)
{
    HWND shellDLL_hwnd = FindWindowEx(_hwnd, NULL, L"SHELLDLL_DefView", NULL);
    HWND* ret = (HWND*)_lParam;

    if (shellDLL_hwnd)
    {
        // Succesfully found the first WorkerW containing the SHELLDLL 
        Vizzy::DWM::SHELLDLL_WORKERW_HWND = (long)_hwnd;
        Vizzy::DWM::SHELLDLL_HWND = (long)shellDLL_hwnd;

        // Find the first child i.e. the listview containing the desktop icons.
        Vizzy::DWM::SHELLDLL_LISTVIEW_HWND = (long)FindWindowEx(shellDLL_hwnd, NULL, L"SysListView32", NULL);;

        // Gets the WorkerW Window after the current WorkerW .
        *ret = FindWindowEx(NULL, _hwnd, L"WorkerW", NULL);
    }
    return true;
}
void Vizzy::DWM::initialize()
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
    EnumWindows(EnumWindowsProc, (LPARAM)&wallpaper_workerw_hwnd);

    Vizzy::DWM::WALLPAPER_WORKERW_HWND = (long)wallpaper_workerw_hwnd;
   
}

void Vizzy::DWM::log_hwnds()
{
    Debug::log("----- DWM HWNDS ------");;
    Debug::log("WALLWORKER   :", Vizzy::DWM::WALLPAPER_WORKERW_HWND);
    Debug::log("SHELLDLL     : ", Vizzy::DWM::SHELLDLL_HWND);
    Debug::log("LISTVIEW     :", Vizzy::DWM::SHELLDLL_LISTVIEW_HWND);
    Debug::log("SHELL WORKER : ", Vizzy::DWM::SHELLDLL_WORKERW_HWND);
    Debug::log("----------------------");;

}
