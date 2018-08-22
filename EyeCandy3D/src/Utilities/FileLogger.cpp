#include "EC3D/Utilities/FileLogger.h"

#include <sstream>

namespace utl
{
	FileLogger::FileLogger()
		: m_indentationFill{' '}
	{
	}

	FileLogger::~FileLogger()
	= default;

	void FileLogger::writeToFile(const char* filepath, const char* data)
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

	void FileLogger::open(const char* filepath)
	{
		if(m_out.is_open())
		{
			m_out.close();
		}
		
		const auto fp = appendDate(filepath);
		m_out.open(fp);
	}

	void FileLogger::close()
	{
		if(m_out.is_open())
		{
			m_out.close();
		}
	}

	void FileLogger::applyIndentation()
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

	void FileLogger::newLine()
	{
		if(!m_out.is_open())
		{
			return;
		}

		m_out << "\n";
	}

	void FileLogger::indentTab(unsigned int steps)
	{
		m_indentationCurrent += steps;
	}

	void FileLogger::indentSpace(unsigned int spaces)
	{
		m_indentationCurrent += spaces;
	}

	void FileLogger::setIndentationFill(char fillChar)
	{
		m_indentationFill = fillChar;
	}

	char FileLogger::getIndentationFill() const
	{
		return m_indentationFill;
	}

	void FileLogger::indentReverseTab(unsigned int steps)
	{
		m_indentationCurrent -= steps * m_indentationStep;
		m_indentationCurrent = m_indentationCurrent < 0 ? 0 : m_indentationCurrent;
	}

	void FileLogger::indentReverseSpace(unsigned int spaces)
	{
		m_indentationCurrent -= spaces;
		m_indentationCurrent = m_indentationCurrent < 0 ? 0 : m_indentationCurrent;
	}

	void FileLogger::resetIndentation()
	{
		m_indentationCurrent = 0;
	}

	unsigned int FileLogger::getCurrentIndentation() const
	{
		return m_indentationCurrent;
	}

	void FileLogger::setIndentation(unsigned int indentation)
	{
		m_indentationCurrent = indentation;
	}

	unsigned int FileLogger::getIndentationStep() const
	{
		return m_indentationStep;
	}

	void FileLogger::setIndentationStep(unsigned int step)
	{
		m_indentationStep = step;
	}

	std::string FileLogger::getSystemDateFormatted()
	{
		return getSystemDateFormatted(s_dateDivider);
	}

	std::string FileLogger::getSystemDateFormatted(char divider)
	{
		const auto now = getSystemDateTime();
		const auto h = (now.tm_hour + 2);
		const auto day = h < 24 ? now.tm_mday : now.tm_mday + 1;
		const auto month = now.tm_mon + 1;
		const auto year = now.tm_year + 1900;

		std::ostringstream date;
		date << day;
		date << divider;
		date << month;
		date << divider;
		date << year;

		return date.str();
	}

	std::string FileLogger::getSystemTimeFormatted()
	{
		return getSystemTimeFormatted(s_timeDivider);
	}

	std::string FileLogger::getSystemTimeFormatted(char divider)
	{
		auto now = getSystemDateTime();
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

	tm FileLogger::getSystemDateTime()
	{
		auto now = time(nullptr);
		tm gmtm{};
		gmtime_s(&gmtm, &now);
		return gmtm;
	}

	std::string FileLogger::getSystemDateTimeFormatted()
	{
		return getSystemDateTimeFormatted(s_dateDivider, '-', s_timeDivider);
	}

	std::string FileLogger::getSystemDateTimeFormatted(char dateDivider, char dateTimeDivider, char timeDivider)
	{
		std::ostringstream dateTime;
		dateTime << getSystemDateFormatted(dateDivider);
		dateTime << dateTimeDivider;
		dateTime << getSystemTimeFormatted(timeDivider);
		return dateTime.str();
	}

	void FileLogger::setDateDivisor(char divider)
	{
		s_dateDivider = divider;
	}

	void FileLogger::setTimeDivisor(char divider)
	{
		s_timeDivider = divider;
	}

	std::string FileLogger::appendDate(const char* filepath) const
	{
		std::string temp = filepath;

		const auto extensionPos = temp.find_last_of('.');
		const auto pathWithoutExtension = temp.substr(0, extensionPos);
		const auto extension = temp.substr(extensionPos, temp.size());

		std::ostringstream strm;
		strm << pathWithoutExtension;
		strm << '_';
		strm << getSystemDateTimeFormatted('-', '#', '-');
		strm << extension;
		return strm.str();
	}

	char FileLogger::s_dateDivider = '-';
	char FileLogger::s_timeDivider = ':';
}