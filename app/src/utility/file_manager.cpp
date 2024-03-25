
#include <fstream>
#include <ostream>
#include <sstream>
#include <Windows.h>
#include <ShlObj.h>

#include "../../headers/utility/files.h"
#include "../../headers/utility/debug.h"


using namespace Vizzy;
std::string Vizzy::FileManager::read_file(const char* _filename)
{
	std::ifstream file;
	std::stringstream buff;//readbuffer

	//open file to read
	file.open(_filename);

	if (file.is_open())
		buff << file.rdbuf();
	else
		Debug::log("Error opening file ", _filename);

	//once done close the file
	file.close();

	return buff.str();
}
 int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{

	if (uMsg == BFFM_INITIALIZED)
	{
		std::string tmp = (const char*)lpData;
		std::cout << "path: " << tmp << std::endl;
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	}

	return 0;
}

 Vizzy::OpenFolderDialogResult Vizzy::FileManager::open_folder_dialog()
{
	//default empty result
	OpenFolderDialogResult result;

	TCHAR path[MAX_PATH];

	std::string pathtemp = "";
	const char* path_param = pathtemp.c_str();
	BROWSEINFO bi = { 0 };

	bi.lpszTitle = L"Browse for folder...";
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = (LPARAM)path_param;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != 0)
	{
		//get the name of the folder and put it in path
		SHGetPathFromIDList(pidl, path);

		//free memory used
		IMalloc* imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
		
		//packs the result
		std::wstring ws(path);
		result.result = SUCCCESS;
		result.path = std::string(ws.begin(), ws.end());


		return result;
	}

	return result;

}

