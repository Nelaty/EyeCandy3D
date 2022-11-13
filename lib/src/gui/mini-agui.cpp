#include "ec3/gui/mini-agui.h"

#include "ec3/gui/backend/ogl-font-loader.h"
#include "ec3/gui/backend/ogl-graphics.h"
#include "ec3/gui/backend/ogl-image-loader.h"
#include "ec3/gui/backend/ogl-input.h"

#include <Agui/Image.hpp>
#include <Agui/Font.hpp>
#include <Agui/Widget.hpp>

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
		s_font = agui::Font::load("../res_sample_0815/Fonts/proza-libre/ProzaLibre-Regular.ttf", 16);
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
