#pragma once

#include <string>
#include <vector>

/**
* File utility functions
*/
namespace utl
{
	std::string getFileContentString(const char* filepath);
	std::vector<std::string> getFileContentSeparatedString(const char* filepath);

	void writeToFileLocal(const std::string& inputStr, const char* filename);


	void createFileInWorkingDirectory(const char* filename);
	void createDirectoryInWorkingDirectory(const char* dirname);
	bool isFileInWorkingDir(const char* filename);
	bool isDirectoryInWorkingDir(const char* dirname);

	void createFilePath(const char* filename, const char* filepath);
	void createDirectoryPath(const char* filename, const char* filepath);
	bool isFileInPath(const char* filename, const char* filepath);
	bool isDirectoryInPath(const char* filename, const char* filepath);
}