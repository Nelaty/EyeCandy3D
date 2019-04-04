#include "EC3D/GUI/Backend/OpenGLFont.h"
#include "EC3D/Core/FontTextureAtlas.h"


namespace ec
{
	
	OpenGLFont::OpenGLFont()
		: m_font{nullptr},
		m_height{0},
		m_lineHeight{0},
		m_autoFree{false}
	{
	}

	OpenGLFont::OpenGLFont(const std::string &fileName,
	                       const int height,
	                       const agui::FontFlags fontFlags,
	                       const float borderWidth,
	                       const agui::Color borderColor)
	{
		m_font = nullptr;
		reload(fileName,
			   height,
			   fontFlags,
			   borderWidth,
			   borderColor);
	}

	OpenGLFont::~OpenGLFont()
	{
		if(m_autoFree)
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
		m_font = font;
		if(!font)
		{
			throw agui::Exception("OpenGLFont::setFont: Given font was null!\n");
		}

		m_autoFree = autoFree;
		m_path = path;

		/// \todo implement
		// height = ???;
		m_lineHeight = m_height;
		
	}

	ec::FontTextureAtlas* OpenGLFont::getFont() const
	{
		return m_font;
	}

	int OpenGLFont::getLineHeight() const
	{
		return m_lineHeight;
	}

	int OpenGLFont::getHeight() const
	{
		return m_height;
	}

	int OpenGLFont::getTextWidth(const std::string &text) const
	{

		return 0;
	}

	const std::string& OpenGLFont::getPath() const
	{
		return m_path;
	}

	void OpenGLFont::reload(const std::string &fileName,
							int height,
	                        agui::FontFlags fontFlags, 
							float borderWidth, 
							agui::Color borderColor)
	{
		if(m_font)
		{
			free();
		}



	}

	void OpenGLFont::free()
	{
		delete m_font;
		m_font = nullptr;
	}

}