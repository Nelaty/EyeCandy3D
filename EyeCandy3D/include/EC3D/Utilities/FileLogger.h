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
		FileLogger();
		~FileLogger();

		static void WriteToFile(const char* filepath, const char* data);

		/* Set the currently active file */
		void Open(const char* filepath);
		/* Close the currently active file */
		void Close();

		/* Append a variable number of elements */
		template<class T, class... Args>
		void Append(T arg, Args... args);
		template<class T>
		void Append(T arg);

		/* Create new line and apply indentation */
		void ApplyIndentation();
		void NewLine();

		/* Indent by a given step */
		void IndentTab(const unsigned int steps);
		/* Indent by one space */
		void IndentSpace(const unsigned int spaces);

		/* Set the filling character of indentation */
		void SetIndentationFill(const char fillChar);
		char GetIndentationFill() const;

		/* Reverse indentation */
		void IndentReverseTab(const unsigned int steps);
		void IndentReverseSpace(const unsigned int spaces);
		void ResetIndentation();

		/* Current indentation*/
		unsigned int GetCurrentIndentation() const;
		void SetIndentation(const unsigned int indentation);

		/* Tab indentation size */
		unsigned int GetIndentationStep() const;
		void SetIndentationStep(const unsigned int step);
		
		/* Time and date functions */
		static std::string GetSystemDateFormatted();
		static std::string GetSystemDateFormatted(const char divider);
		static std::string GetSystemTimeFormatted();
		static std::string GetSystemTimeFormatted(const char divider);
		static tm GetSystemDateTime();
		static std::string GetSystemDateTimeFormatted();
		static std::string GetSystemDateTimeFormatted(const char dateDivider, const char dateTimeDivider,const char timeDivider);

		/* Set the character, which divides hour, minutes, seconds etc. */
		static void SetDateDivisor(const char divider);
		/* Set the character, which divides year, month, day etc. */
		static void SetTimeDivisor(const char divider);

	private:
		std::ofstream m_out;

		std::string AppendDate(const char* filepath);

		bool m_appendCurrentDate;

		char m_indentationFill;

		static char s_dateDivider;
		static char s_timeDivider;

		unsigned int m_indentationStep;
		unsigned int m_indentationCurrent;
	};


	template<class T, class... Args>
	void utl::FileLogger::Append(T arg, Args... args)
	{
		if(m_out.is_open())
		{
			m_out << arg;
			Append(args...);
		}
	}

	template<class T>
	void utl::FileLogger::Append(T arg)
	{
		if(m_out.is_open())
		{
			m_out << arg;
		}
	}
}