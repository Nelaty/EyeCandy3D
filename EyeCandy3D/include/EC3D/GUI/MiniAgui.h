#pragma once
#include "EC3D/Common/Common.h"

namespace agui
{
	class Font;
}

namespace ec
{
	class OpenGLImageLoader;
	class OpenGLFontLoader;

	class EC3D_DECLSPEC MiniAgui
	{
	public:
		static void init();

	private:
		explicit MiniAgui();
		~MiniAgui();
	
		static OpenGLImageLoader* s_imageLoader;
		static OpenGLFontLoader* s_fontLoader;
		static agui::Font* s_font;
	};
}