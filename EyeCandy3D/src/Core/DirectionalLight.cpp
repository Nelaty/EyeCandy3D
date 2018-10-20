#include "EC3D/Core/DirectionalLight.h"

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
		/// \todo: implement -> get direction from node
		return {};
	}
}
