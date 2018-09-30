#pragma once
#include "EC3D/Common/Common.h"


namespace ec
{
	/**
	* Track the time passed since the timer was initialized last
	* and the time between calls.
	*/
	class EC3D_DECLSPEC Timer
	{
	public:
		explicit Timer();
		~Timer();

		/** Reset the whole timer */
		void reset();

		/** Only reset the time since the last access of time delta */
		void resetTimeDelta();

		/** Get time since the start of the timer or last reset */
		static double getTime();
		/** Set the timer to a specific time. */
		static void setTime(double time);
		/** Get time between calls */
		double getTimeDelta();

	private:
		double m_timeDeltaFirst{};
		double m_timeDeltaLast{};
	};
}