#include "EC3D/Utilities/FileLogger.h"

#include <sstream>

namespace utl
{
	FileLogger::FileLogger()
		: m_appendCurrentDate{true},
		m_indentationStep{4},
		m_indentationCurrent{0},
		m_indentationFill{' '}
	{
	}

	FileLogger::~FileLogger()
	{
		if(m_out.is_open())
		{
			m_out.close();
		}
	}

	void FileLogger::WriteToFile(const char* filepath, const char* data)
	{
		std::ofstream out;
		out.open(filepath);
		if(!out.is_open())
		{
			return;
		}
		out << data;
		out.close();
	}

	void FileLogger::Open(const char* filepath)
	{
		if(m_out.is_open())
		{
			m_out.close();
		}

		auto fp = AppendDate(filepath);

		m_out.open(fp);
		if(!m_out.is_open())
		{
			return;
		}
	}

	void FileLogger::Close()
	{
		if(m_out.is_open())
		{
			m_out.close();
		}
	}

	void FileLogger::ApplyIndentation()
	{
		if(!m_out.is_open())
		{
			return;
		}

		for(unsigned int j = 0; j < m_indentationCurrent; ++j)
		{
			m_out << m_indentationFill;
		}
	}

	void FileLogger::NewLine()
	{
		if(!m_out.is_open())
		{
			return;
		}

		m_out << "\n";
	}

	void FileLogger::IndentTab(const unsigned int steps)
	{
		m_indentationCurrent += steps;
	}

	void FileLogger::IndentSpace(const unsigned int spaces)
	{
		m_indentationCurrent += spaces;
	}

	void FileLogger::SetIndentationFill(const char fillChar)
	{
		m_indentationFill = fillChar;
	}

	char FileLogger::GetIndentationFill() const
	{
		return m_indentationFill;
	}

	void FileLogger::IndentReverseTab(const unsigned int steps)
	{
		m_indentationCurrent -= steps * m_indentationStep;
		m_indentationCurrent = m_indentationCurrent < 0 ? 0 : m_indentationCurrent;
	}

	void FileLogger::IndentReverseSpace(const unsigned int spaces)
	{
		m_indentationCurrent -= spaces;
		m_indentationCurrent = m_indentationCurrent < 0 ? 0 : m_indentationCurrent;
	}

	void FileLogger::ResetIndentation()
	{
		m_indentationCurrent = 0;
	}

	unsigned int FileLogger::GetCurrentIndentation() const
	{
		return m_indentationCurrent;
	}

	void FileLogger::SetIndentation(const unsigned int indentation)
	{
		m_indentationCurrent = indentation;
	}

	unsigned int FileLogger::GetIndentationStep() const
	{
		return m_indentationStep;
	}

	void FileLogger::SetIndentationStep(const unsigned int step)
	{
		m_indentationStep = step;
	}

	std::string FileLogger::GetSystemDateFormatted()
	{
		return GetSystemDateFormatted(s_dateDivider);
	}

	std::string FileLogger::GetSystemDateFormatted(const char divider)
	{
		auto now = GetSystemDateTime();
		auto h = (now.tm_hour + 2);
		auto day = h < 24 ? now.tm_mday : now.tm_mday + 1;
		auto month = now.tm_mon + 1;
		auto year = now.tm_year + 1900;

		std::ostringstream date;
		date << day;
		date << divider;
		date << month;
		date << divider;
		date << year;

		return date.str();
	}

	std::string FileLogger::GetSystemTimeFormatted()
	{
		return GetSystemTimeFormatted(s_timeDivider);
	}

	std::string FileLogger::GetSystemTimeFormatted(const char divider)
	{
		auto now = GetSystemDateTime();
		auto s = now.tm_sec;
		auto m = now.tm_min;
		auto h = (now.tm_hour + 2) % 24;

		std::ostringstream timeStrm;
		if(h < 10)
			timeStrm << '0';
		timeStrm << h;
		timeStrm << divider;
		if(m < 10)
			timeStrm << '0';
		timeStrm << m;
		timeStrm << divider;
		if(s < 10)
			timeStrm << '0';
		timeStrm << s;

		return timeStrm.str();
	}

	tm FileLogger::GetSystemDateTime()
	{
		time_t now = time(0);
		tm gmtm;
		gmtime_s(&gmtm, &now);
		return gmtm;
	}

	std::string FileLogger::GetSystemDateTimeFormatted()
	{
		return GetSystemDateTimeFormatted(s_dateDivider, '-', s_timeDivider);
	}

	std::string FileLogger::GetSystemDateTimeFormatted(const char dateDivider, const char dateTimeDivider, const char timeDivider)
	{
		std::ostringstream dateTime;
		dateTime << GetSystemDateFormatted(dateDivider);
		dateTime << dateTimeDivider;
		dateTime << GetSystemTimeFormatted(timeDivider);
		return dateTime.str();
	}

	void FileLogger::SetDateDivisor(const char divider)
	{
		s_dateDivider = divider;
	}

	void FileLogger::SetTimeDivisor(const char divider)
	{
		s_timeDivider = divider;
	}

	std::string FileLogger::AppendDate(const char* filepath)
	{
		std::string temp = filepath;

		size_t extensionPos = temp.find_last_of('.');
		std::string pathWithoutExtension = temp.substr(0, extensionPos);
		std::string extension = temp.substr(extensionPos, temp.size());

		std::ostringstream strm;
		strm << pathWithoutExtension;
		strm << '_';
		strm << GetSystemDateTimeFormatted('-', '#', '-');
		strm << extension;
		return strm.str();
	}

	char FileLogger::s_dateDivider = '-';
	char FileLogger::s_timeDivider = ':';
}