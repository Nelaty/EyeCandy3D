#include "EC3D/Utilities/FileSystem.h"

#include <filesystem>

namespace ec
{
	void FileSystem::createDirectory(const std::string& dir)
	{
		std::experimental::filesystem::create_directory(dir);
	}

	FileSystem::FileSystem()
	= default;

	FileSystem::~FileSystem()
	= default;
}
