#pragma once
#include "Agui/Rectangle.hpp"
#include "EC3D/Graphics/Material/Texture.h"

#include <glm/glm.hpp>

namespace ec
{
	struct GuiShaderInfoObject
	{
		agui::Rectangle m_clippingRect;

		glm::vec2 m_position;
		glm::vec2 m_offset;
		glm::vec2 m_size;

		glm::vec4 m_color;

		Texture m_texture;
		bool m_usesTexture{false};
		bool m_isText{false};
	};
}