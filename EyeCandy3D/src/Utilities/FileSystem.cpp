#include "EC3D/Utilities/FileSystem.h"

#if defined(_WIN32)
	#include <filesystem>
#else
	#include <sys/stat.h>
#endif

namespace ec
{
	void FileSystem::createDirectory(const std::string& dir)
	{
	#if defined(_WIN32)
		std::experimental::filesystem::create_directory(dir);
	#else
		mkdir(dir.c_str(), 755);
	#endif
	}

	FileSystem::FileSystem()
	= default;

	FileSystem::~FileSystem()
	= default;
}
