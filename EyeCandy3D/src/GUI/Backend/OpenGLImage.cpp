#include "EC3D/GUI/Backend/OpenGLImage.h"

namespace agui
{
	OpenGLImage::OpenGLImage()
	{
	}

	OpenGLImage::OpenGLImage(const std::string& fileName, bool convertMask)
	{
		m_texture.TextureFromFile(fileName.c_str(), 
								  ec::TextureTypes::GetTypeString(ec::TextureTypes::Type::texture_diffuse));
	}

	OpenGLImage::~OpenGLImage()
	{
		if(m_autoFree)
		{
			m_texture.Free();
		}
	}

	int OpenGLImage::getWidth() const
	{
		return m_width;
	}

	int OpenGLImage::getHeight() const
	{
		return m_height;
	}

	agui::Color OpenGLImage::getPixel(int x, int y) const
	{
		/// \todo implement
		return Color();
	}

	void OpenGLImage::setPixel(int x, int y, const Color& color)
	{
		/// \todo implement
	}

	void OpenGLImage::setTexture(ec::Texture texture, bool autoFree)
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
		m_texture.Free();
	}
}