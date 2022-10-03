#pragma once
#include "EC3D/Common/Common.h"

#include "glm/glm.hpp"

#include <random>

namespace ec
{
	/**
	* Equally distributed random number generator.
	*/
	class EC3D_DECLSPEC Random
	{
	public:
		/** Seed the random number generator with a random value. */
		static void seed();
		/** Seed the random number generator with a given seed. */
		static void seed(unsigned int seed);
        /** Seed the random number generator with a given seed. */
        static void seed(std::seed_seq seed);

        /** Calculate random integer value. */
		static int randomInt();
		static int randomInt(int min, int max);
			
		/** Calculate random float value. */
		static float randomFloat();
		static float randomFloat(float min, float max);
		static float randomFloatZeroOne();

		/** Calculate random double value. */
		static double randomDouble();
		static double randomDouble(double min, double max);
		static double randomDoubleZeroOne();

		/** Calculate a random 2D vector. */
		static glm::vec2 randomVec2();
		/** Calculate a random 2D vector. */
		static glm::vec2 randomVec2(float min, float max);
		/** Calculate a random 2D vector. */
		static glm::vec2 randomVec2(const glm::vec2& min, 
									const glm::vec2& max);

		/** Calculate a random 3D vector. */
		static glm::vec3 randomVec3();
		/** Calculate a random 3D vector. */
		static glm::vec3 randomVec3(float min, float max);
		/** Calculate a random 3D vector. */
		static glm::vec3 randomVec3(const glm::vec3& min,
									const glm::vec3& max);

		/** Calculate a random 4D vector. */
		static glm::vec4 randomVec4();
		/** Calculate a random 4D vector. */
		static glm::vec4 randomVec4(float min, float max);
		/** Calculate a random 4D vector. */
		static glm::vec4 randomVec4(const glm::vec4& min,
									const glm::vec4& max);

		/** 
		 * Get a random boolean value. 
		 * \param chance The probability of the boolean value to be true.
		 */
		static bool randomBool(float chance);

	private:
		explicit Random() = default;
		~Random() = default;

        static std::mt19937 s_rng;
        static std::mt19937_64 s_rng64;
	};
}
