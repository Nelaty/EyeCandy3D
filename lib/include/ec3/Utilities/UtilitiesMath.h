#pragma once
#include "ec3/Common/Common.h"

namespace ec
{
	/**
	 * \brief Check if a given number is a prime number.
	 * \param number The number to be examined.
	 * \return True if the number is a prime number, false otherwise.
	 */
	template<class T>
	EC3D_DECLSPEC bool isPrime(T number)
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
		for(auto i = 2; i < numSqrt; ++i)
		{
			if((number % i) == 0)
			{
				return false;
			}
		}
		return true;
	}
}