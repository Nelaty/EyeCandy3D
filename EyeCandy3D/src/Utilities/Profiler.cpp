#include "EC3D/Utilities/Profiler.h"

#include <chrono>

namespace ec
{
	namespace
	{
		unsigned int evaluateProfilingPrecision(std::chrono::steady_clock::time_point start,
										 std::chrono::steady_clock::time_point end,
										 ProfilingPrecision precision)
		{
			using namespace std::chrono;

			switch(precision)
			{
				case ProfilingPrecision::second:
					return unsigned int(duration_cast<seconds>(end - start).count());
				case ProfilingPrecision::millisecond:
					return unsigned int(duration_cast<milliseconds>(end - start).count());
				case ProfilingPrecision::microsecond:
					return unsigned int(duration_cast<microseconds>(end - start).count());
				case ProfilingPrecision::nanosecond:
					return unsigned int(duration_cast<nanoseconds>(end - start).count());

				default:
					printf("ERROR Profiler: precision not defined!\n");
					return unsigned int(duration_cast<seconds>(end - start).count());
			}
		}	
	}

	void ProfilingData::print() const
	{
		printf("Number of executions: %d\n", m_loops);
		if(m_loops > 1)
		{
			printf("Time taken:\n");
			printf("- min: %d%s\n", m_min, m_precisionPostfix.c_str());
			printf("- max: %d%s\n", m_max, m_precisionPostfix.c_str());
			printf("- avg: %d%s\n", m_avg, m_precisionPostfix.c_str());
		}
		else
		{
			printf("Time taken: %d%s\n", m_min, m_precisionPostfix.c_str());
		}
	}

	void ProfilingData::setPrecision(ProfilingPrecision precision)
	{
		m_precision = precision;

		switch(precision)
		{
			case ProfilingPrecision::second:
				m_precisionPostfix = "s";
				break;
			case ProfilingPrecision::millisecond:
				m_precisionPostfix = "ms";
				break;
			case ProfilingPrecision::microsecond:
				m_precisionPostfix = "us";
				break;
			case ProfilingPrecision::nanosecond:
				m_precisionPostfix = "ns";
				break;
			default:
				m_precisionPostfix = "";
				break;

		}
	}

	ec::ProfilingPrecision ProfilingData::getPrecision() const
	{
		return m_precision;
	}

	ProfilingData profileFunction(const std::function<void()>& f,
								  const unsigned int loops,
								  const ProfilingPrecision precision)
	{
		ProfilingData data;
		data.m_loops = loops;
		data.setPrecision(precision);

		auto tempMin = UINT_MAX;
		unsigned int tempMax = 0;
		unsigned int tempAvg = 0;

		for(unsigned int i = 0; i < loops; ++i)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			f();
			const auto end = std::chrono::high_resolution_clock::now();
			auto timeTaken = evaluateProfilingPrecision(start, end, precision);

			tempAvg += timeTaken;

			tempMin = tempMin < timeTaken ? tempMin : timeTaken;
			tempMax = tempMax > timeTaken ? tempMax : timeTaken;
		}

		data.m_min = tempMin;
		data.m_max = tempMax;
		data.m_avg = tempAvg / data.m_loops;
		
		return data;
	}
}