#include "ec3/utilities/timer.h"

#include "GLFW/glfw3.h"

namespace ec
{
	Timer::Timer()
	{
		reset();
	}

	Timer::~Timer()
	= default;

	//void Timer::reset()
	//{
	//	m_start = glfwGetTime();
	//	m_timeDeltaFirst = m_start;
	//	m_timeDeltaLast = m_start;
	//}

	//void Timer::resetTimeDelta()
	//{
	//	m_timeDeltaFirst = m_timeDeltaLast;
	//}

	//double Timer::getTime() const
	//{
	//	return glfwGetTime() - m_start;
	//}

	//void Timer::setTime(const double time)
	//{
	//	glfwSetTime(time);
	//}

	//double Timer::getTimeDelta()
	//{
	//	m_timeDeltaLast = glfwGetTime();
	//	return m_timeDeltaLast - m_timeDeltaFirst;
	//}

	void Timer::reset()
	{
		setTime(0.0f);
		m_timeDeltaFirst = 0.0f;
		m_timeDeltaLast = 0.0f;
	}

	void Timer::resetTimeDelta()
	{
		m_timeDeltaFirst = m_timeDeltaLast;
	}

	double Timer::getTime()
	{
		return glfwGetTime();
	}

	void Timer::setTime(const double time)
	{
		glfwSetTime(time);
	}

	double Timer::getTimeDelta()
	{
		m_timeDeltaLast = getTime();
		return m_timeDeltaLast - m_timeDeltaFirst;
	}
}