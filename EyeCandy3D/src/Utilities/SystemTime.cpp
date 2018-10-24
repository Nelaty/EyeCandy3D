#include "EC3D/Utilities/SystemTime.h"

#include <sstream>

namespace ec
{
	SystemTime::SystemTime()
	{
		update();
	}

	SystemTime::~SystemTime()
		= default;

	void SystemTime::update()
	{
		auto now = time(nullptr);
		localtime_s(&m_timeInfo, &now);
	}
	 
	std::string SystemTime::getTimeAndDateFormatted() const
	{
		const auto time = getTimeFormatted();
		const auto date = getDateFormatted();

		return date + "." + time;
	}

	std::string SystemTime::getTimeFormatted(const char delimiter) const
	{
		std::ostringstream oss;
		oss << getHours() << delimiter << getMinutes() << delimiter << getSeconds();
		return oss.str();
	}

	std::string SystemTime::getDateFormatted(const char delimiter) const
	{
		std::ostringstream oss;
		oss << getYear() << delimiter << getMonth() << delimiter << getMonthDay();
		return oss.str();
	}

	std::string SystemTime::getMonthString() const
	{
		switch(getMonth())
		{
			case 1: return "January";
			case 2: return "February";
			case 3: return "March";
			case 4: return "April";
			case 5: return "May";
			case 6: return "June";
			case 7: return "July";
			case 8: return "August";
			case 9: return "September";
			case 10: return "October";
			case 11: return "November";
			case 12: return "December";

			default: return "UNKNOWN MONTH";
		}
	}

	std::string SystemTime::getWeekDayString() const
	{
		switch(getWeekDay())
		{
			case 0: return "Sunday";
			case 1: return "Monday";
			case 2: return "Tuesday";
			case 3: return "Wednesday";
			case 4: return "Thursday";
			case 5: return "Friday";
			case 6: return "Saturday";

			default: return "UNKNOWN WEEK DAY";
		}
	}

	int SystemTime::getSeconds() const
	{
		return m_timeInfo.tm_sec + 1;
	}

	int SystemTime::getMinutes() const
	{
		return m_timeInfo.tm_min + 1;
	}

	int SystemTime::getHours() const
	{
		return m_timeInfo.tm_hour + 1;
	}

	int SystemTime::getMonthDay() const
	{
		return m_timeInfo.tm_mday;
	}

	int SystemTime::getMonth() const
	{
		return m_timeInfo.tm_mon + 1;
	}

	int SystemTime::getYear() const
	{
		return m_timeInfo.tm_year + 1900;
	}

	int SystemTime::getWeekDay() const
	{
		return m_timeInfo.tm_wday;
	}

	int SystemTime::getYearDay() const
	{
		return m_timeInfo.tm_yday + 1;
	}

	bool SystemTime::isDaylightSavingsDay() const
	{
		return m_timeInfo.tm_isdst != 0;
	}
}
