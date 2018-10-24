#pragma once
#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Core/Freetype.h"

namespace ec
{
	struct GuiRenderContext
	{
		Shader* m_guiShader;
		Shader* m_textShader;
		Freetype* m_freetype;
	};
}