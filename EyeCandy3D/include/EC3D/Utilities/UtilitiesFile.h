#pragma once
#include "EC3D/Common/Common.h"

#include <string>
#include <vector>

/**
* File utility functions
*/
namespace utl
{
	EC3D_DECLSPEC std::string getFileContentString(const char* filepath);
	EC3D_DECLSPEC std::vector<std::string> getFileContentSeparatedString(const char* filepath);

	EC3D_DECLSPEC void writeToFileLocal(const std::string& inputStr, const char* filename);


	EC3D_DECLSPEC void createFileInWorkingDirectory(const char* filename);
	EC3D_DECLSPEC void createDirectoryInWorkingDirectory(const char* dirname);
	EC3D_DECLSPEC bool isFileInWorkingDir(const char* filename);
	EC3D_DECLSPEC bool isDirectoryInWorkingDir(const char* dirname);

	EC3D_DECLSPEC void createFilePath(const char* filename, const char* filepath);
	EC3D_DECLSPEC void createDirectoryPath(const char* filename, const char* filepath);
	EC3D_DECLSPEC bool isFileInPath(const char* filename, const char* filepath);
	EC3D_DECLSPEC bool isDirectoryInPath(const char* filename, const char* filepath);
}