#include "EC3D/Graphics/Lighting/SpotLight.h"

namespace ec
{
	SpotLight::SpotLight(const glm::vec2& halfAngles)
		: Light(LightType::spot),
		m_halfAngles(halfAngles)
	{
	}

	const glm::vec3& SpotLight::getDirection() const
	{
		return m_direction;
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
