#pragma once

/*
* Math utility functions
*/

namespace utl
{
	template<class T>
	bool IsPrime(T number)
	{
		if(number < 4)
		{
			if(number > 1)
			{
				return true;
			}
			return false;
		}

		T numSqrt = sqrt(number) + 1;
		for(int i = 2; i < numSqrt; ++i)
		{
			if((number % i) == 0)
			{
				return false;
			}
		}
		return true;
	}
}