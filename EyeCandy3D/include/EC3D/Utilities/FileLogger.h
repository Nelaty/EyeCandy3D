#pragma once

#include <string>
#include <fstream>
#include <ctime>

/*
* A file logger offers various formatting options on how and
* what to write to a file.
*/
namespace utl
{
	class FileLogger
	{
	public:
		explicit FileLogger();
		~FileLogger();

		static void writeToFile(const char* filepath, const char* data);

		/* Set the currently active file */
		void open(const char* filepath);
		/* Close the currently active file */
		void close();

		/* Append a variable number of elements */
		template<class T, class... Args>
		void append(T arg, Args... args);
		template<class T>
		void append(T arg);

		/* Create new line and apply indentation */
		void applyIndentation();
		void newLine();

		/* Indent by a given step */
		void indentTab(unsigned int steps);
		/* Indent by one space */
		void indentSpace(unsigned int spaces);

		/* Set the filling character of indentation */
		void setIndentationFill(char fillChar);
		char getIndentationFill() const;

		/* Reverse indentation */
		void indentReverseTab(unsigned int steps);
		void indentReverseSpace(unsigned int spaces);
		void resetIndentation();

		/* Current indentation*/
		unsigned int getCurrentIndentation() const;
		void setIndentation(unsigned int indentation);

		/* Tab indentation size */
		unsigned int getIndentationStep() const;
		void setIndentationStep(unsigned int step);
		
		/* Time and date functions */
		static std::string getSystemDateFormatted();
		static std::string getSystemDateFormatted(char divider);
		static std::string getSystemTimeFormatted();
		static std::string getSystemTimeFormatted(char divider);
		static tm getSystemDateTime();
		static std::string getSystemDateTimeFormatted();
		static std::string getSystemDateTimeFormatted(char dateDivider, char dateTimeDivider, char timeDivider);

		/* Set the character, which divides hour, minutes, seconds etc. */
		static void setDateDivisor(char divider);
		/* Set the character, which divides year, month, day etc. */
		static void setTimeDivisor(char divider);

	private:
		std::ofstream m_out;

		std::string appendDate(const char* filepath) const;

		char m_indentationFill;

		static char s_dateDivider;
		static char s_timeDivider;

		unsigned int m_indentationStep = 4;
		unsigned int m_indentationCurrent = 0;
	};


	template<class T, class... Args>
	void utl::FileLogger::append(T arg, Args... args)
	{
		if(m_out.is_open())
		{
			m_out << arg;
			append(args...);
		}
	}

	template<class T>
	void utl::FileLogger::append(T arg)
	{
		if(m_out.is_open())
		{
			m_out << arg;
		}
	}
}