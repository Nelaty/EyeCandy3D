#include "ec3/graphics/lighting/point-light.h"

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
