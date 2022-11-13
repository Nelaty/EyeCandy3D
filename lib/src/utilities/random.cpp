#include "ec3/utilities/random.h"

#include <cassert>
#include <utility>
#include <ctime>
#include <random>

namespace ec
{
	void Random::seed()
	{
        std::random_device rd;
        seed(rd());
	}

	void Random::seed(const unsigned int seed)
	{
	    s_rng.seed(seed);
        s_rng64.seed(seed);
	}

    void Random::seed(std::seed_seq seed)
    {
        s_rng.seed(seed);
        s_rng64.seed(seed);
    }

	int Random::randomInt()
	{
	    return s_rng();
	}

	int Random::randomInt(const int min, const int max)
	{
		assert(min <= max);
		return s_rng() % (max - min) + min;
	}

	float Random::randomFloat()
	{
		return randomFloatZeroOne() * FLT_MAX;
	}

	float Random::randomFloat(const float min, const float max)
	{
		assert(min <= max);
		return randomFloatZeroOne() * (max - min) + min;
	}

	float Random::randomFloatZeroOne()
	{
	    return float(s_rng()) / float(s_rng.max());
	}

	double Random::randomDouble()
	{
		return randomDoubleZeroOne() * DBL_MAX;
	}

	double Random::randomDouble(const double min, const double max)
    {
		assert(min <= max);
		return randomDoubleZeroOne() * (max - min) + min;
	}

	double Random::randomDoubleZeroOne()
	{
	    return double(s_rng64()) / double(s_rng64.max());
	}

	glm::vec2 Random::randomVec2()
	{
		return glm::vec2(randomFloat(), randomFloat());
	}

	glm::vec2 Random::randomVec2(const float min, const float max)
	{
		return glm::vec2(randomFloat(min, max),
						 randomFloat(min, max));
	}

	glm::vec2 Random::randomVec2(const glm::vec2& min, const glm::vec2& max)
	{
		return glm::vec2(randomFloat(min.x, max.x),
						 randomFloat(min.y, max.y));
	}

	glm::vec3 Random::randomVec3()
	{
		return glm::vec3(randomFloat(), randomFloat(), randomFloat());
	}

	glm::vec3 Random::randomVec3(const float min, const float max)
	{
		return glm::vec3(randomFloat(min, max),
						 randomFloat(min, max),
						 randomFloat(min, max));
	}

	glm::vec3 Random::randomVec3(const glm::vec3& min, const glm::vec3& max)
	{
		return glm::vec3(randomFloat(min.x, max.x),
						 randomFloat(min.y, max.y),
						 randomFloat(min.z, max.z));
	}

	glm::vec4 Random::randomVec4()
	{
		return glm::vec4(randomFloat(), randomFloat(), randomFloat(), randomFloat());
	}

	glm::vec4 Random::randomVec4(const float min, const float max)
	{
		return glm::vec4(randomFloat(min, max),
						 randomFloat(min, max),
						 randomFloat(min, max),
						 randomFloat(min, max));
	}

	glm::vec4 Random::randomVec4(const glm::vec4& min, const glm::vec4& max)
	{
		return glm::vec4(randomFloat(min.x, max.x),
						 randomFloat(min.y, max.y),
						 randomFloat(min.z, max.z),
						 randomFloat(min.w, max.w));
	}

	bool Random::randomBool(const float chance)
	{
		return randomFloatZeroOne() < chance;
	}

	std::mt19937 Random::s_rng = std::mt19937();
	std::mt19937_64 Random::s_rng64 = std::mt19937_64();
}
