#pragma once
#include "EC3D/Core/Light.h"

#include <glm/glm.hpp>

namespace ec
{
	class SpotLight : public Light
	{
	public:
		explicit SpotLight(const glm::vec2& halfAngles = glm::vec2(glm::radians(45)));
		~SpotLight();

		/** Get the direction the light is facing at. */
		const glm::vec3& getDirection() const;

		/** 
		 * Set the current half angles, which determin the size of the
		 * spotlight.
		 */
		void setHalfAngles(const glm::vec2& halfAngles);
		/**
		* Set the current half angles, which determin the size of the
		* spotlight.
		*/
		void setHalfAngles(float halfAngle);
		/** Get the current half angles. */
		const glm::vec2& getHalfAngles() const;
		
	private:
		glm::vec2 m_halfAngles;
	};
}