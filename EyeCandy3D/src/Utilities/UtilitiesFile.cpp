#include "EC3D/Utilities/UtilitiesFile.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

#include <GL/glew.h>

namespace utl
{
	std::string GetFileContentString(const char* filepath)
	{
		std::ifstream in(filepath);
		std::string fileContent;
		if(in.is_open())
		{
			std::string temp;
			while(!in.eof())
			{
				std::getline(in, temp);
				fileContent.append(temp);
			}
			in.close();
		}
		else
		{
			std::cerr << "Couldn't open " << filepath << "!\n";
		}

		return std::move(fileContent);
	}

	std::vector<std::string> GetFileContentSeparatedString(const char* filepath)
	{
		std::ifstream in(filepath);
		std::string fileContent;
		std::vector<std::string> separetedFileContent;

		if(in.is_open())
		{
			std::string temp;
			while(!in.eof())
			{
				std::getline(in, temp);
				fileContent.append(temp);
			}
			in.close();

			std::istringstream iss(fileContent);
			std::copy(std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				std::back_inserter(separetedFileContent));
		}
		else
		{
			std::cerr << "Couldn't open \"" << filepath << "\"!\n";
		}

		return std::move(separetedFileContent);
	}

	void WriteToFileLocal(const std::string& inputStr, const char* filename)
	{
		std::ofstream out;
		out.open(filename);
		if(!out.is_open())
		{
			return;
		}

		out << inputStr;
		out.close();
	}

	// TODO: implement
	void CreateFileInWorkingDirectory(const char* filename)
	{

	}

	void CreateDirectoryInWorkingDirectory(const char* dirname)
	{

	}

	bool IsFileInWorkingDir(const char* filename)
	{
		return true;
	}

	bool IsDirectoryInWorkingDir(const char* dirname)
	{
		return true;
	}

	void CreateFilePath(const char* filename, const char* filepath)
	{

	}

	void CreateDirectoryPath(const char* filename, const char* filepath)
	{

	}

	bool IsFileInPath(const char* filename, const char* filepath)
	{
		return true;
	}

	bool IsDirectoryInPath(const char* filename, const char* filepath)
	{
		return true;
	}
}