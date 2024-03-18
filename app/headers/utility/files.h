#pragma once
#include <filesystem>
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>

#include "debug.h"
//access it like sayy Vizzy::FileManager.read_file();
namespace Vizzy {
	class FileManager {
	public:
		static std::string read_file(const char* _filename) {
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
		};

	};
}