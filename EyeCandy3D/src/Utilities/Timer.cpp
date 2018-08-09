#include "EC3D/Utilities/Timer.h"

#include <GLFW/glfw3.h>

namespace ec
{
	Timer::Timer()
	{
		Reset();
	}

	Timer::~Timer()
	{
	}

	void Timer::Reset()
	{
		m_start = glfwGetTime();
		m_timeDeltaFirst = m_start;
		m_timeDeltaLast = m_start;
	}

	void Timer::ResetTimeDelta()
	{
		m_timeDeltaFirst = m_timeDeltaLast;
	}

	double Timer::GetTime() const
	{
		return glfwGetTime() - m_start;
	}

	double Timer::GetTimeDelta()
	{
		m_timeDeltaLast = glfwGetTime();
		return m_timeDeltaLast - m_timeDeltaFirst;
	}
}