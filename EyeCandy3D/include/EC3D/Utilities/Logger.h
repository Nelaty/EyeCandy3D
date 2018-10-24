#pragma once

#include <string>
#include <map>
#include <fstream>

namespace ec
{
	/**
	 * \brief Describes how much will be outputted to console.
	 */
	enum class LoggingDepth
	{
		basic,
		error_only,
		all
	};

	/**
	 * \brief Describes the category of a logging message. 
	 */
	enum class LoggingCategory
	{
		info,
		warning,
		error
	};

	/**
	 * \brief Log messages to console and create log files.
	 */
	class Logger
	{
	public:
		/**
		 * \brief Logger constructor
		 * \param depth Depth with which messages will be logged
		 * \param logDir The directory in which new logs will be created
		 */
		explicit Logger(LoggingDepth depth = LoggingDepth::all, 
						const std::string& logDir = "Logs");
		~Logger();

		/**
		 * \brief Open another file for logging
		 * \param logFile File path to the log file
		 * \param overwrite Overwrite an existing file if set to true
		 * \return True if the log file was opened, false otherwise
		 */
		bool openLogFile(const std::string& logFile = "", 
						 bool overwrite = false);

		/**
		 * \brief Log a message
		 * \param msg The message to log
		 * \param category The category of the message
		 */
		void log(const std::string& msg, 
				 LoggingCategory category = LoggingCategory::info);

	private:

		/**
		 * \brief Log message with "basic" depth
		 * \param msg The message to log
		 * \param category The category of the message
		 */
		void logBasic(const std::string& msg, LoggingCategory category);
		/**
		 * \brief Log message with "error_only" depth
		 * \param msg The message to log
		 * \param category The category of the message
		 */
		void logErrorOnly(const std::string& msg, LoggingCategory category);
		/**
		 * \brief Log message with "all" depth
		 * \param msg The message to log
		 * \param category The category of the message
		 */
		void logAll(const std::string& msg, LoggingCategory category);

		/**
		 * \brief Generate the name for a new file
		 * \param baseName Base name of the file
		 * \param systemDate Append system date to file name?
		 * \param systemTime Append system time to file name?
		 * \return The file name
		 */
		static std::string generateFileName(const std::string& baseName, 
											bool systemDate = true,
											bool systemTime = true);

		/**
		 * \brief Prepare a message
		 * \param msg The message base text
		 * \param category The category of the message
		 * \return The formatted message as seen by the user
		 */
		static std::string formatMessage(const std::string& msg, 
										 LoggingCategory category);

		/**
		 * \brief Print a message to console
		 * \param msg The message to print
		 */
		static void consolePrint(const std::string& msg);
		/**
		 * \brief Print a message to the current log file
		 * \param msg The message to print
		 */
		void filePrint(const std::string& msg);

		/**
		 * \brief Convert a LoggingCategory to a string
		 * \param category The category to convert
		 * \return The string representation of the category
		 */
		static const std::string& categoryToString(LoggingCategory category);
		static const std::map<LoggingCategory, std::string> s_categoryString;

		std::string m_logDirectory;
		std::string m_logName;
		std::string m_logPath;
		std::ofstream m_outFile;

		LoggingDepth m_depth;

		static constexpr const char* s_logFileExtension = ".txt";
	};
}
