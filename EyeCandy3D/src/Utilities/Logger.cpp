#include "EC3D/Utilities/Logger.h"
#include "EC3D/Utilities/FileSystem.h"
#include "EC3D/Utilities/SystemTime.h"

#include <iostream>

namespace ec
{
	Logger::Logger(const LoggingDepth depth, 
				   const std::string& logDir)
		: m_logDirectory(logDir),
		m_logName(""),
		m_logPath(""),
		m_depth(depth)
	{
		FileSystem::createDirectory(logDir);
	}

	Logger::~Logger()
	= default;

	bool Logger::openLogFile(const std::string& logFile,
							 const bool overwrite)
	{
		auto fileName = generateFileName(logFile);
		auto path = m_logDirectory + "/" + fileName;

		m_outFile.open(path, std::ios::app);
		const auto exists = m_outFile.is_open();

		if(exists)
		{
			if(!overwrite)
			{
				return false;
			}
			m_outFile.close();
			m_outFile.open(path, std::ios::out | std::ios::trunc);
		}

		if(!m_outFile.is_open())
		{
			return false;
		}

		m_logName = logFile;
		m_logPath = path;
		return true;
	}

	void Logger::log(const std::string& msg,
	                 const LoggingCategory category)
	{
		switch (m_depth)
		{
			case LoggingDepth::basic:
			{
				logBasic(msg, category);
				break;
			}
			case LoggingDepth::error_only:
			{
				logErrorOnly(msg, category);
				break;
			}
			case LoggingDepth::all: 
			{
				logAll(msg, category);
				break;
			}

			default:
			{
				printf("ERROR: Logging category \"%d\" doesn't exist!", 
					   static_cast<int>(category));
				break;
			};
		}
	}

	void Logger::logBasic(const std::string& msg, 
						  const LoggingCategory category)
	{
		if(category == LoggingCategory::warning
		   || category == LoggingCategory::error)
		{
			const auto formatted = formatMessage(msg, category);
			consolePrint(formatted);
			filePrint(formatted);
		}
	}

	void Logger::logErrorOnly(const std::string& msg, 
							  const LoggingCategory category)
	{
		if (category == LoggingCategory::error)
		{
			const auto formatted = formatMessage(msg, category);
			consolePrint(formatted);
			filePrint(formatted);
		}
	}

	void Logger::logAll(const std::string& msg, 
						const LoggingCategory category)
	{
		const auto formatted = formatMessage(msg, category);
		consolePrint(formatted);
		filePrint(formatted);
	}

	std::string Logger::generateFileName(const std::string& baseName, 
										 const bool systemDate,
										 const bool systemTime)
	{
		SystemTime t;

		auto name = baseName;
		if (systemDate)
		{
			name.append("_");
			name.append(t.getDateFormatted());
			name.append(".");
		}
		else if(systemTime)
		{
			name.append("_");
		}
		
		if(systemTime)
		{
			name.append(t.getTimeFormatted('_'));
		}

		return name + s_logFileExtension;
	}

	std::string Logger::formatMessage(const std::string& msg, 
									  const LoggingCategory category)
	{
		return categoryToString(category) + ": " + msg + "\n";
	}

	void Logger::consolePrint(const std::string& msg)
	{
		printf("%s", msg.c_str());
	}

	void Logger::filePrint(const std::string& msg)
	{
		if(m_outFile.is_open())
		{
			m_outFile << msg;
		}
	}

	const std::string& Logger::categoryToString(const LoggingCategory category)
	{
		return s_categoryString.at(category);
	}

	const std::map<LoggingCategory, std::string> Logger::s_categoryString =
	{
		{ LoggingCategory::info, "INFO" },
		{ LoggingCategory::warning, "WARNING" },
		{ LoggingCategory::error, "ERROR" }
	};
}
