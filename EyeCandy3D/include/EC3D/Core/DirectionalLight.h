#pragma once
#include "EC3D/Core/Light.h"

#include <glm/glm.hpp>

namespace ec
{
	/**
	 * \brief A light source that emits light in a given direction
	 * independently of its position.
	 */
	/// \todo: implement
	class DirectionalLight : public Light
	{
	public:
		explicit DirectionalLight();
		~DirectionalLight();

		/**
		 * \brief Get the current direction in which light will be
		 * emitted.
		 */
		const glm::vec3& getDirection() const;
	};
}