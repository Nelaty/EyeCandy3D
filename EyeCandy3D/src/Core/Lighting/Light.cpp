#include "EC3D/Core/Lighting/Light.h"

namespace ec
{
	Light::Light(LightType type, float intensity, const ec::Color& color)
		: m_type(type),
		m_color{color},
		m_intensity{intensity}
	{
	}

	Light::~Light()
	{
	}
}
