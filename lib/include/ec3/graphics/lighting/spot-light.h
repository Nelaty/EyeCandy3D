#pragma once
#include "ec3/graphics/lighting/light.h"

#include <glm/glm.hpp>

namespace ec
{
	/// Light source with a direction and a conical shape.
	/// \todo: implement
	class SpotLight : public Light
	{
	public:
		/// SpotLight constructor.
		/// \param halfAngles Determines the size of the light cone.
		///        In radians.
		explicit SpotLight(const glm::vec2& halfAngles = glm::vec2(glm::radians(45.f)));
		~SpotLight();

		/// Set the current half angles, which determine the 
		/// size of the spotlight.
		void setHalfAngles(const glm::vec2& halfAngles);
		/// Set the current half angles, which determine 
		/// the size of the spotlight.
		void setHalfAngles(float halfAngle);
		/// Get the current half angles. 
		const glm::vec2& getHalfAngles() const;
		
	private:
		glm::vec2 m_halfAngles;
	};
}
