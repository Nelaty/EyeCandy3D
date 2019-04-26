#include "EC3D/Core/Lighting/PointLight.h"

namespace ec
{
	PointLight::PointLight(const float falloff)
		: Light(LightType::spot),
		m_falloff(falloff)
	{
	}

	PointLight::~PointLight()
	{
	}
}
