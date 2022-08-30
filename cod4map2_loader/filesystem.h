#pragma once

#include "h.h"

#ifndef fysilesystem
#define fysilesystem

namespace F
{
	std::string F_GetExeFileName();
	std::string F_GetExePath();

	std::string F_GetFileName(std::string path);

	void F_GoToPreviousDirectory(std::string* directory);
	std::string F_GoToPreviousDirectory(std::string directory);

	std::string F_GetFileExtension(std::string file);
	std::string F_removeFileExtension(std::string file, size_t chars);

	enum class fileopen
	{
		FILE_IN = 1,
		FILE_OUT = 2,
		FILE_APP = 8,
		FILE_BINARY = 32
	};

	bool F_OpenFile(std::fstream* fp, std::string path, fileopen type);
	bool F_CloseFile(std::fstream* fp);

	bool F_FileBelongsToThisDirectory(std::string directory, std::string file);
	template<typename t> void F_FilesInThisDirectory(std::string directory, std::vector<t>* out);
}

#endif
