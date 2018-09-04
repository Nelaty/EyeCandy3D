#include "UnitTest++/UnitTest++.h"

SUITE(Test_Suite)
{
	TEST(Equality_1)
	{
		CHECK_EQUAL(1, 2);
	}
	TEST(Equality_2)
	{
		CHECK_EQUAL(1, 1);
	}
}
