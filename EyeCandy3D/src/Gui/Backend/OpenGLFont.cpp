#include "ec3/Gui/Backend/OpenGLFont.h"
#include "ec3/Graphics/Text/FontTextureAtlas.h"


namespace ec
{
	
	OpenGLFont::OpenGLFont()
		: font{nullptr},
		height{0},
		lineHeight{0},
		autoFree{false}
	{
	}

	OpenGLFont::OpenGLFont(const std::string &fileName,
	                       const int height,
	                       const agui::FontFlags fontFlags,
	                       const float borderWidth,
	                       const agui::Color borderColor)
	{
		font = nullptr;
		reload(fileName,
			   height,
			   fontFlags,
			   borderWidth,
			   borderColor);
	}

	OpenGLFont::~OpenGLFont()
	{
		if(autoFree)
		{
			OpenGLFont::free();
		}
	}

	void OpenGLFont::setFont(ec::FontTextureAtlas* font, 
							 const std::string &path,
	                         const bool autoFree)
	{
		if(autoFree)
		{
			free();
		}
		this->font = font;
		if(!font)
		{
			throw agui::Exception("OpenGLFont::setFont: Given font was null!\n");
		}

		this->autoFree = autoFree;
		this->path = path;

		/// \todo implement
		// height = ???;
		lineHeight = height;
		
	}

	ec::FontTextureAtlas* OpenGLFont::getFont() const
	{
		return this->font;
	}

	int OpenGLFont::getLineHeight() const
	{
		return this->lineHeight;
	}

	int OpenGLFont::getHeight() const
	{
		return this->height;
	}

	int OpenGLFont::getTextWidth(const std::string &text) const
	{
		/// \todo implement
		return 0;
	}

	const std::string& OpenGLFont::getPath() const
	{
		return this->path;
	}

	void OpenGLFont::reload(const std::string &fileName,
							int height,
	                        agui::FontFlags fontFlags, 
							float borderWidth, 
							agui::Color borderColor)
	{
		if(font)
		{
			free();
		}

		/// \todo implement
	}

	void OpenGLFont::free()
	{
		delete font;
		font = nullptr;
	}

}
