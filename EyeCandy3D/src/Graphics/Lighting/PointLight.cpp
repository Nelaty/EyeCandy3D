#include "ec3/Graphics/Lighting/PointLight.h"

namespace ec
{
	PointLight::PointLight(const float falloff)
		: Light(LightType::spot),
		m_falloff(falloff)
	{
	}

	PointLight::~PointLight()
	= default;

	void PointLight::setFalloff(const float falloff)
	{
		m_falloff = falloff;
	}

	float PointLight::getFalloff() const
	{
		return m_falloff;
	}
}
