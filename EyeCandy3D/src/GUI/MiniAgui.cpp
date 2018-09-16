#include "EC3D/Gui/MiniAgui.h"

#include <Agui/Image.hpp>
#include <Agui/Font.hpp>
#include <Agui/Widget.hpp>
#include "EC3D/Gui/Backend/OpenGLImageLoader.h"
#include "EC3D/Gui/Backend/OpenGLFontLoader.h"
#include "EC3D/Gui/Backend/OpenGLInput.h"
#include "EC3D/Gui/Backend/OpenGLGraphics.h"

namespace ec
{
	void MiniAgui::init()
	{
		// Set the image loader
		s_imageLoader = new OpenGLImageLoader();
		agui::Image::setImageLoader(s_imageLoader);

		// Set the font loader
		s_fontLoader = new OpenGLFontLoader();
		agui::Font::setFontLoader(s_fontLoader);

		// Allegro does not automatically premultiply alpha so let Agui do it
		agui::Color::setPremultiplyAlpha(true);

		// Setting a global font is required and failure to do so will crash.
		s_font = agui::Font::load("../Resources/Fonts/proza-libre/ProzaLibre-Regular.ttf", 16);
		agui::Widget::setGlobalFont(s_font);
	}

	OpenGLImageLoader* MiniAgui::s_imageLoader = nullptr;
	OpenGLFontLoader* MiniAgui::s_fontLoader = nullptr;
	agui::Font* MiniAgui::s_font = nullptr;

	MiniAgui::MiniAgui()
	= default;

	MiniAgui::~MiniAgui()
	= default;
}
