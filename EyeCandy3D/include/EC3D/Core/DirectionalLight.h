#pragma once
#include "EC3D/Core/Light.h"

#include <glm/glm.hpp>

namespace ec
{
	class DirectionalLight : public Light
	{
	public:
		explicit DirectionalLight();
		~DirectionalLight();
		
		const glm::vec3& getDirection() const;
	};
}