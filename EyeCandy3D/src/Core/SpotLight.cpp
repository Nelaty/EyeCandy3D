#include "EC3D/Core/SpotLight.h"

namespace ec
{
	SpotLight::SpotLight(const glm::vec2& halfAngles)
		: Light(LightType::spot),
		m_halfAngles(halfAngles)
	{
	}

	SpotLight::~SpotLight()
	= default;

	const glm::vec3& SpotLight::getDirection() const
	{
		/// \todo: implement -> get direction from node
		return {};
	}

	void SpotLight::setHalfAngles(const glm::vec2& halfAngles)
	{
		m_halfAngles = halfAngles;
	}

	void SpotLight::setHalfAngles(float halfAngle)
	{
		m_halfAngles.x = halfAngle;
		m_halfAngles.y = halfAngle;
	}

	const glm::vec2& SpotLight::getHalfAngles() const
	{
		return m_halfAngles;
	}
}
