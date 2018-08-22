#pragma once
#include <functional>
#include <string>

namespace utl
{
	/* Profiling precisions, which data can be represented in */
	enum class ProfilingPrecision
	{
		second,
		millisecond,
		microsecond,
		nanosecond
	};

	/* Bundles results from profiling */
	struct ProfilingData
	{	
	public:
		void print() const;
	
		unsigned int m_loops;
		unsigned int m_min;
		unsigned int m_avg;
		unsigned int m_max;

		void setPrecision(ProfilingPrecision precision);
		ProfilingPrecision getPrecision() const;

	private:
		std::string m_precisionPostfix;
		ProfilingPrecision m_precision = ProfilingPrecision::millisecond;
	};

	/* Profile a single function */
	ProfilingData profileFunction(const std::function<void()>& f,
								  unsigned int loops = 1,
								  ProfilingPrecision precision = ProfilingPrecision::millisecond);
}