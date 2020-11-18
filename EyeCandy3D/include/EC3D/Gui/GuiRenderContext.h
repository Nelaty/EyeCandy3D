#pragma once
#include "EC3D/Graphics/Shader/Shader.h"
#include "EC3D/Graphics/Text/Freetype.h"

namespace ec
{
	struct GuiRenderContext
	{
		Shader* m_guiShader;
		Shader* m_textShader;
		Freetype* m_freetype;
	};
}