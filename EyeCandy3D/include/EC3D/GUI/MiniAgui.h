#pragma once

namespace agui
{
	class OpenGLImageLoader;
	class OpenGLFontLoader;
	class Font;
}

namespace ec
{
	class MiniAgui
	{
	public:
		static void init();

	private:
		explicit MiniAgui();
		~MiniAgui();
	
		static agui::OpenGLImageLoader* s_imageLoader;
		static agui::OpenGLFontLoader* s_fontLoader;
		static agui::Font* s_font;
	};
}