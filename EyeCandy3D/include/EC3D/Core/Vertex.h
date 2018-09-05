#pragma once
#include "EC3D/Common/Common.h"

#include <glm/glm.hpp>

namespace ec
{
	struct EC3D_DECLSPEC Vertex
	{
		glm::vec3 m_position;
		glm::vec3 m_normal;
		glm::vec2 m_texCoords;
	};
}