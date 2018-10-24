#pragma once
#include <string>
#include <ctime>

namespace ec
{
	class SystemTime
	{
	public:
		explicit SystemTime();
		~SystemTime();

		/**
		 * \brief Update this structures internal time and date to the
		 * current one.
		 */
		void update();

		/**
		 * \brief Get the current time and date combined in a string
		 * \return Date and time
		 */
		std::string getTimeAndDateFormatted() const;

		/**
		 * \brief Get the time as a formatted string
		 * \return Time
		 */
		std::string getTimeFormatted(char delimiter = ':') const;
		/**
		 * \brief Get the date as a formatted string
		 * \return Date
		 */
		std::string getDateFormatted(char delimiter = '-') const;

		/**
		 * \brief Get the month as a string
		 * \return Month
		 */
		std::string getMonthString() const;
		/**
		 * \brief Get the weekday as a string
		 * \return Week day
		 */
		std::string getWeekDayString() const;

		/**
		 * \brief Get seconds after the current minute
		 * \return Seconds [1, 60]
		 */
		int getSeconds() const;
		/**
		 * \brief Get minutes after the current hour
		 * \return Minutes [1, 60]
		 */
		int getMinutes() const;
		/**
		 * \brief Get hour of the current day
		 * \return Hours [1, 24]
		 */
		int getHours() const;
		/**
		 * \brief Get the day of the current month
		 * \return Day [1, 31]
		 */
		int getMonthDay() const;
		/**
		 * \brief Get the month of the current year
		 * \return Month [1, 12]
		 */
		int getMonth() const;
		/**
		 * \brief Get the current year
		 * \return Year
		 */
		int getYear() const;
		/**
		 * \brief Get the number of days after the last sunday
		 * \return Week day [0, 6]
		 */
		int getWeekDay() const;
		/**
		 * \brief Get the day of the current year
		 * \return [1, 366]
		 */
		int getYearDay() const;
		/**
		 * \brief Check for daylight savings day
		 * \return True if it is daylight savings day, false otherwise
		 */
		bool isDaylightSavingsDay() const;

	private:
		tm m_timeInfo;
	};
}
