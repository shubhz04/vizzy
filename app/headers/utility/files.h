#pragma once
#include <iostream>
#include <vector>
namespace Vizzy {

#pragma region OpenSaveDialogs
	enum OpenDialogResult { SUCCCESS, EMPTY };


	//---- Select Folder Dialog Box ----
	// result contains a response field and a path for the selected directory 
	struct OpenFolderDialogResult {
		OpenDialogResult result;
		std::string path;

		OpenFolderDialogResult() {
			result = EMPTY;
			path = "";
		};
	};
#pragma endregion

	class FileManager {
	public:

		//opens a new dialog box while stalling the caller thread until a response
		static OpenFolderDialogResult open_folder_dialog();


		//reads utf-8 encoded files
		static std::string read_file(const char* _filename);

		//list all files provided by filetype
		static std::vector<std::string> list_files(const char* _directory);
	
	
	};
};