#pragma once
#include "Agui/FontLoader.hpp"

namespace agui
{
	class OpenGLFontLoader : public FontLoader
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
