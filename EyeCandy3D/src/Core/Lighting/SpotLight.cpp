#include "EC3D/Core/Lighting/SpotLight.h"

namespace ec
{
	SpotLight::SpotLight(const glm::vec2& halfAngles)
		: Light(LightType::spot),
		m_halfAngles(halfAngles)
	{
	}

	SpotLight::~SpotLight()
	{
	}
}
