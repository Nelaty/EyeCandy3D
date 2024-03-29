#pragma once
#include "ec3/graphics/lighting/light.h"

#include <glm/glm.hpp>

namespace ec
{
	/// A light source that emits light in a given direction
	/// independent of its position.
	/// \todo: implement
	class DirectionalLight : public Light
	{
	public:
		explicit DirectionalLight();
		~DirectionalLight();
	};
}