#include "EC3D/GUI/Backend/OpenGLFontLoader.h"
#include "EC3D/GUI/Backend/OpenGLFont.h"

namespace ec
{
	
	OpenGLFontLoader::OpenGLFontLoader()
	= default;

	OpenGLFontLoader::~OpenGLFontLoader()
	= default;


	agui::Font* OpenGLFontLoader::loadFont(const std::string &fileName,
	                                       const int height,
	                                       const agui::FontFlags fontFlags,
	                                       const float borderWidth,
	                                       const agui::Color borderColor)
	{
		return new OpenGLFont(fileName,
							  height,
							  fontFlags,
							  borderWidth,
							  borderColor);
	}

	
	agui::Font* OpenGLFontLoader::loadEmptyFont()
	{
		return new ec::OpenGLFont();
	}

}