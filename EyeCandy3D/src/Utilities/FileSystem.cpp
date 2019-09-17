#include "EC3D/Utilities/FileSystem.h"

#include <filesystem>


#ifdef _WIN32 || _WIN64
#include <windows.h>
#elif defined __unix__
 
#endif

namespace ec
{
	void FileSystem::createDirectory(const std::string& dir)
	{
		std::experimental::filesystem::create_directory(dir);
	}

	std::string FileSystem::getOpenFileName()
	{
	#ifdef _WIN32 || _WIN64
		OPENFILENAME ofn;
		char fileName[MAX_PATH] = "";
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = NULL;
		ofn.lpstrFilter = NULL;
		ofn.lpstrFile = fileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrDefExt = "";
		ofn.lpstrInitialDir = "";

		bool ok = GetOpenFileName(&ofn);
		if(!ok) return "";

		return fileName;
	#elif defined __unix__
		return "";
	#endif
	}

	FileSystem::FileSystem()
	{
	}

	FileSystem::~FileSystem()
	{
	}
}