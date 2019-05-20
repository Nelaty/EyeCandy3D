#pragma once
#include "EC3D/Core/Light.h"

#include <glm/glm.hpp>

namespace ec
{
	/**
	 * \brief Light source with a direction and a conical shape.
	 * \todo: implement
	 */
	class SpotLight : public Light
	{
	public:
		/**
		 * \brief SpotLight constructor.
		 * \param halfAngles Determines the size of the light cone.
		 * In radians.
		 */
		explicit SpotLight(const glm::vec2& halfAngles = glm::vec2(glm::radians(45.f)));
		~SpotLight();

		/** 
		 * \brief Get the direction the light is facing at. 
		 */
		const glm::vec3& getDirection() const;

		/** 
		 * \brief Set the current half angles, which determine the 
		 * size of the spotlight.
		 */
		void setHalfAngles(const glm::vec2& halfAngles);
		/**
		* \brief Set the current half angles, which determine 
		* the size of the spotlight.
		*/
		void setHalfAngles(float halfAngle);
		/**
		 * \brief Get the current half angles. 
		 */
		const glm::vec2& getHalfAngles() const;
		
	private:
		glm::vec2 m_halfAngles;
	};
}
