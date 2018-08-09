#pragma once

#include <string>
#include <vector>

/*
* File utility functions
*/

namespace utl
{
	std::string GetFileContentString(const char* filepath);
	std::vector<std::string> GetFileContentSeparatedString(const char* filepath);

	void WriteToFileLocal(const std::string& inputStr, const char* filename);


	void CreateFileInWorkingDirectory(const char* filename);
	void CreateDirectoryInWorkingDirectory(const char* dirname);
	bool IsFileInWorkingDir(const char* filename);
	bool IsDirectoryInWorkingDir(const char* dirname);

	void CreateFilePath(const char* filename, const char* filepath);
	void CreateDirectoryPath(const char* filename, const char* filepath);
	bool IsFileInPath(const char* filename, const char* filepath);
	bool IsDirectoryInPath(const char* filename, const char* filepath);
}