#pragma once
#include "ec3/common/common.h"

#include <glm/glm.hpp>

namespace ec
{
	/**
	 * \brief Contains vertex information used for rendering.
	 */
	struct EC3D_DECLSPEC Vertex
	{
		glm::vec3 m_position;
		glm::vec3 m_normal;
		glm::vec2 m_texCoords;
	};
}