#include "ec3/Gui/Backend/OpenGLImage.h"

namespace ec
{
	OpenGLImage::OpenGLImage()
		= default;

	OpenGLImage::OpenGLImage(const std::string& fileName, bool convertMask)
	{
		m_texture.textureFromFile(fileName.c_str(), 
								  ec::TextureTypes::getTypeString(ec::TextureTypes::Type::texture_diffuse));
	}

	OpenGLImage::~OpenGLImage()
	{
		if(m_autoFree)
		{
			m_texture.free();
		}
	}

	int OpenGLImage::getWidth() const
	{
		return m_texture.getWidth();
	}

	int OpenGLImage::getHeight() const
	{
		return m_texture.getHeight();
	}

	agui::Color OpenGLImage::getPixel(int x, int y) const
	{
		/// \todo implement
		return {};
	}

	void OpenGLImage::setPixel(int x, int y, const agui::Color& color)
	{
		/// \todo implement
	}

	void OpenGLImage::setTexture(const ec::Texture& texture, const bool autoFree)
	{
		if(m_autoFree)
		{
			free();
		}

		m_texture = texture;
		m_autoFree = autoFree;
	}

	const ec::Texture& OpenGLImage::getTexture() const
	{
		return m_texture;
	}

	bool OpenGLImage::isAutoFreeing() const
	{
		return m_autoFree;
	}

	void OpenGLImage::free()
	{
		m_texture.free();
	}
}
