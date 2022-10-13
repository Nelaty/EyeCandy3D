#pragma once
#include "ec3/Graphics/Shader/Shader.h"
#include "ec3/Graphics/Text/Freetype.h"

namespace ec
{
	struct GuiRenderContext
	{
		Shader* m_guiShader;
		Shader* m_textShader;
		Freetype* m_freetype;
	};
}