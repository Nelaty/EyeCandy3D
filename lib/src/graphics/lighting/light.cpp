#include "ec3/graphics/lighting/light.h"

namespace ec
{
	Light::Light(const LightType type,
				 const float intensity, 
				 const glm::vec3& color)
		: m_color{color},
		m_intensity{intensity},
		m_type(type)
	{
	}

	Light::~Light()
	= default;

	void Light::setColor(const glm::vec3& color)
	{
		m_color = color;
	}

	void Light::setColor(const float r,
						 const float g,
						 const float b)
	{
		m_color.r = r;
		m_color.g = g;
		m_color.b = b;
	}

	const glm::vec3& Light::getColor() const
	{
		return m_color;
	}

	void Light::setIntensity(const float intensity)
	{
		m_intensity = intensity;
	}

	float Light::getIntensity() const
	{
		return m_intensity;
	}
}
