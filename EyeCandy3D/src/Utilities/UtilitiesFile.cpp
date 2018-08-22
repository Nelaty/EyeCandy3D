#include "EC3D/Utilities/UtilitiesFile.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

namespace utl
{
	std::string getFileContentString(const char* filepath)
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

		return fileContent;
	}

	std::vector<std::string> getFileContentSeparatedString(const char* filepath)
	{
		std::ifstream in(filepath);
		std::string fileContent;
		std::vector<std::string> separatedFileContent;

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
				std::back_inserter(separatedFileContent));
		}
		else
		{
			std::cerr << "Couldn't open \"" << filepath << "\"!\n";
		}

		return separatedFileContent;
	}

	void writeToFileLocal(const std::string& inputStr, const char* filename)
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
	void createFileInWorkingDirectory(const char* filename)
	{

	}

	void createDirectoryInWorkingDirectory(const char* dirname)
	{

	}

	bool isFileInWorkingDir(const char* filename)
	{
		return true;
	}

	bool isDirectoryInWorkingDir(const char* dirname)
	{
		return true;
	}

	void createFilePath(const char* filename, const char* filepath)
	{

	}

	void createDirectoryPath(const char* filename, const char* filepath)
	{

	}

	bool isFileInPath(const char* filename, const char* filepath)
	{
		return true;
	}

	bool isDirectoryInPath(const char* filename, const char* filepath)
	{
		return true;
	}
}