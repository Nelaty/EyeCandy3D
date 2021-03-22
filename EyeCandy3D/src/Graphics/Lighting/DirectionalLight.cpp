#include "EC3D/Graphics/Lighting/DirectionalLight.h"

namespace ec
{
	DirectionalLight::DirectionalLight()
		: Light(LightType::directional)
	{
	}

	DirectionalLight::~DirectionalLight()
	= default;

	const glm::vec3& DirectionalLight::getDirection() const
	{
		return m_direction;
	}
}
