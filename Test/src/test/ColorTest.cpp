#include "EC3D/Core/Color.h"
#include "UnitTest++/UnitTest++.h"

#include "EC3D/Utilities/Random.h"

#include <vector>

UNITTEST_SUITE(ColorTests)
{
	constexpr float s_epsilon = 0.0001f;

	UNITTEST_TEST(ColorRgb)
	{
		glm::ivec4 colorVal(ec::Random::randomInt(0, 255),
							ec::Random::randomInt(0, 255),
							ec::Random::randomInt(0, 255),
							ec::Random::randomInt(0, 255));

		auto color = ec::Color::createRgb(colorVal.r, colorVal.g, colorVal.b, colorVal.a);
		
		UNITTEST_CHECK_CLOSE(float(colorVal.r) / 255.0f, color.getR(), s_epsilon);
		UNITTEST_CHECK_CLOSE(float(colorVal.g) / 255.0f, color.getG(), s_epsilon);
		UNITTEST_CHECK_CLOSE(float(colorVal.b) / 255.0f, color.getB(), s_epsilon);
		UNITTEST_CHECK_CLOSE(float(colorVal.a) / 255.0f, color.getA(), s_epsilon);
	}

	UNITTEST_TEST(ColorRgbF)
	{
		ec::Color color;
		auto randCol = ec::Random::randomVec4(glm::vec4(0.0), glm::vec4(1.0));
		auto colorRgb = ec::Color::createRgbF(randCol.r, randCol.g, randCol.b, randCol.a);

		UNITTEST_CHECK_CLOSE(randCol.r, colorRgb.getR(), s_epsilon);
		UNITTEST_CHECK_CLOSE(randCol.g, colorRgb.getG(), s_epsilon);
		UNITTEST_CHECK_CLOSE(randCol.b, colorRgb.getB(), s_epsilon);
		UNITTEST_CHECK_CLOSE(randCol.a, colorRgb.getA(), s_epsilon);
	}

	UNITTEST_TEST(ColorHexRgb)
	{
		std::vector<int> borders =
		{
			0x00, 0x01, 0xFE, 0xFF
		};

		for(const auto& r : borders)
		{
			for(const auto& g : borders)
			{
				for(const auto& b : borders)
				{
					int hex = (r << 16) + (g << 8) + b;
					auto color = ec::Color::createHexRgb(hex);

					UNITTEST_CHECK_CLOSE(float(r) / 255.0f, color.getR(), s_epsilon);
					UNITTEST_CHECK_CLOSE(float(g) / 255.0f, color.getG(), s_epsilon);
					UNITTEST_CHECK_CLOSE(float(b) / 255.0f, color.getB(), s_epsilon);
				}
			}
		}
	}

	UNITTEST_TEST(ColorHexRgbString)
	{
		ec::Color color;
		std::vector<std::pair<std::string, int>> borders =
		{
			{"00", 0x00}, {"01", 0x01}, {"FE", 0xFE}, {"FF", 0xFF}
		};
		std::vector<std::string> suffixes =
		{
			"", "0x"
		};

		for(auto& r : borders)
		{
			for(auto& g : borders)
			{
				for(auto& b : borders)
				{
					for(auto& suf : suffixes)
					{
						std::string colorString = suf + r.first + g.first + b.first;
						auto color = ec::Color::createHexRgb(colorString);

						UNITTEST_CHECK_CLOSE(float(r.second) / 255.0f, color.getR(), s_epsilon);
						UNITTEST_CHECK_CLOSE(float(g.second) / 255.0f, color.getG(), s_epsilon);
						UNITTEST_CHECK_CLOSE(float(b.second) / 255.0f, color.getB(), s_epsilon);
					}			
				}
			}
		}
	}

	UNITTEST_TEST(ColorHexRgba)
	{
		std::vector<int> borders =
		{
			0x00, 0x01, 0xFE, 0xFF
		};

		for(const auto& r : borders)
		{
			for(const auto& g : borders)
			{
				for(const auto& b : borders)
				{
					for(const auto& a : borders)
					{
						int hex = (r << 24) + (g << 16) + (b << 8) + a;
						auto color = ec::Color::createHexRgba(hex);

						UNITTEST_CHECK_CLOSE(float(r) / 255.0f, color.getR(), s_epsilon);
						UNITTEST_CHECK_CLOSE(float(g) / 255.0f, color.getG(), s_epsilon);
						UNITTEST_CHECK_CLOSE(float(b) / 255.0f, color.getB(), s_epsilon);
						UNITTEST_CHECK_CLOSE(float(a) / 255.0f, color.getA(), s_epsilon);
					}
				}
			}
		}
	}

	UNITTEST_TEST(ColorHexRgbaString)
	{
		ec::Color color;
		std::vector<std::pair<std::string, int>> borders =
		{
			{"00", 0x00},{"01", 0x01},{"FE", 0xFE},{"FF", 0xFF}
		};
		std::vector<std::string> suffixes =
		{
			"", "0x"
		};

		for(auto& r : borders)
		{
			for(auto& g : borders)
			{
				for(auto& b : borders)
				{
					for(auto& a : borders)
					{
						for(auto& suf : suffixes)
						{
							std::string colorString = suf + r.first + g.first + b.first + a.first;
							auto color = ec::Color::createHexRgba(colorString);

							UNITTEST_CHECK_CLOSE(float(r.second) / 255.0f, color.getR(), s_epsilon);
							UNITTEST_CHECK_CLOSE(float(g.second) / 255.0f, color.getG(), s_epsilon);
							UNITTEST_CHECK_CLOSE(float(b.second) / 255.0f, color.getB(), s_epsilon);
							UNITTEST_CHECK_CLOSE(float(a.second) / 255.0f, color.getA(), s_epsilon);
						}
					}
				}
			}
		}
	}

	UNITTEST_TEST(SetGetTest)
	{
		auto randFloat = &ec::Random::randomFloatZeroOne;

		auto r = randFloat();
		auto g = randFloat();
		auto b = randFloat();
		auto a = randFloat();

		ec::Color color;
		color.setR(r);
		color.setG(g);
		color.setB(b);
		color.setA(a);

		UNITTEST_CHECK_EQUAL(r, color.getR());
		UNITTEST_CHECK_EQUAL(g, color.getG());
		UNITTEST_CHECK_EQUAL(b, color.getB());
		UNITTEST_CHECK_EQUAL(a, color.getA());
	}
}