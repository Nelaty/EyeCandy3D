#pragma once
#include "Agui/FontLoader.hpp"
#include "EC3D/Common/Common.h"

namespace agui
{
	class EC3D_DECLSPEC OpenGLFontLoader : public FontLoader
	{
	public:
		explicit OpenGLFontLoader();
		~OpenGLFontLoader();

		Font* loadFont(const std::string &fileName, 
					   int height, 
					   FontFlags fontFlags = FONT_DEFAULT_FLAGS, 
					   float borderWidth = 0, 
					   agui::Color borderColor = agui::Color()) override;
		Font* loadEmptyFont() override;
	};
}
