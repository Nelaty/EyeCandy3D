#pragma once

/*
* Track the time passed since the timer was initialized last
* and the time between calls.
*/
namespace ec
{
	class Timer
	{
	public:
		explicit Timer();
		~Timer();

		/* Reset the whole timer */
		void Reset();

		/* Only reset the time since the last access of time delta */
		void ResetTimeDelta();

		/* Get time since start or the time between calls */
		double GetTime() const;
		double GetTimeDelta();

	private:
		double m_start;

		double m_timeDeltaFirst;
		double m_timeDeltaLast;
	};
}