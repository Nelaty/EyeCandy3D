#include "EC3D/GUI/Backend/OpenGLFontLoader.h"
#include "EC3D/GUI/Backend/OpenGLFont.h"

namespace agui
{
	
	OpenGLFontLoader::OpenGLFontLoader()
	= default;

	OpenGLFontLoader::~OpenGLFontLoader()
	= default;


	agui::Font* OpenGLFontLoader::loadFont(const std::string &fileName,
										   int height,
										   FontFlags fontFlags, 
										   float borderWidth, 
										   agui::Color borderColor)
	{
		return new agui::OpenGLFont(fileName,
									height,
									fontFlags,
									borderWidth,
									borderColor);
	}

	
	agui::Font* OpenGLFontLoader::loadEmptyFont()
	{
		return new agui::OpenGLFont();
	}

}