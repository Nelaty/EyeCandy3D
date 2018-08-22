#include "EC3D/Utilities/Timer.h"

#include <GLFW/glfw3.h>

namespace ec
{
	Timer::Timer()
	{
		reset();
	}

	Timer::~Timer()
	= default;

	void Timer::reset()
	{
		m_start = glfwGetTime();
		m_timeDeltaFirst = m_start;
		m_timeDeltaLast = m_start;
	}

	void Timer::resetTimeDelta()
	{
		m_timeDeltaFirst = m_timeDeltaLast;
	}

	double Timer::getTime() const
	{
		return glfwGetTime() - m_start;
	}

	double Timer::getTimeDelta()
	{
		m_timeDeltaLast = glfwGetTime();
		return m_timeDeltaLast - m_timeDeltaFirst;
	}
}