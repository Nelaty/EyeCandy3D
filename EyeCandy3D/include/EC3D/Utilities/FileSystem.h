#pragma once
#include <string>

namespace ec
{
	/**
	 * \brief Static class, which contains utility file system functions.
	 */
	class FileSystem
	{
	public:
		static void createDirectory(const std::string& dir);

	private:
		explicit FileSystem();
		~FileSystem();
	};
}
