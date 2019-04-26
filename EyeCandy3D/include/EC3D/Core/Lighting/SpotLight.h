#pragma once
#include "Light.h"

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
		explicit SpotLight(const glm::vec2& halfAngles = glm::vec2(glm::radians(45)));
		~SpotLight();

		glm::vec2 m_halfAngles;
	};
}