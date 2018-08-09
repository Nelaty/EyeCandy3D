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
		void Print();
	
		unsigned int m_loops;
		unsigned int m_min;
		unsigned int m_avg;
		unsigned int m_max;

		void SetPrecision(ProfilingPrecision precision);
		ProfilingPrecision GetPrecision() const;

	private:
		std::string m_precisionPostfix;
		ProfilingPrecision m_precision;
	};

	/* Profile a single function */
	ProfilingData ProfileFunction(std::function<void(void)> f,
								  const unsigned int loops = 1,
								  ProfilingPrecision precision = ProfilingPrecision::millisecond);
}