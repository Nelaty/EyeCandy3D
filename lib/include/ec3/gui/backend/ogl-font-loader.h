#pragma once
#include "Agui/FontLoader.hpp"
#include "ec3/common/common.h"

namespace ec
{
	class EC3D_DECLSPEC OpenGLFontLoader : public agui::FontLoader
	{
	public:
		explicit OpenGLFontLoader();
		~OpenGLFontLoader();

		agui::Font* loadFont(const std::string &fileName,					 
							 int height,
							 agui::FontFlags fontFlags = agui::FONT_DEFAULT_FLAGS, 
							 float borderWidth = 0, 
							 agui::Color borderColor = agui::Color()) override;
		agui::Font* loadEmptyFont() override;
	};
}
