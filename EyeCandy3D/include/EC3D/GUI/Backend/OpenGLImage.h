#pragma once

#include "Agui/BaseTypes.hpp"

#include "EC3D/Core/Texture.h"

namespace agui
{
	/** OpenGL back end for images used by Agui */
	class OpenGLImage : public Image
	{		
	public:
		explicit OpenGLImage();
		explicit OpenGLImage(const std::string& fileName, bool convertMask = false);
		virtual ~OpenGLImage();
		
		/** Get the width of the texture. */
		virtual int getWidth() const override;
		/** Get the height of the texture. */
		virtual int getHeight() const override;
		
		/** Get the color of a pixel at a given position */
		virtual Color getPixel(int x, int y) const override;
		/** Set a pixel of the texture at a given position */
		virtual void setPixel(int x, int y, const Color& color) override;
		
		/** Set the texture to a given one. */
		void setTexture(ec::Texture texture, bool autoFree = false);
		/** Get the current texture. */
		const ec::Texture& getTexture() const;
		
		/** Check if the texture gets automatically deallocated */
		virtual bool isAutoFreeing() const override;
		/** Free memory allocated by the texture */
		virtual void free() override;
		
	private:
		ec::Texture m_texture;

		int m_width;
		int m_height;
		bool m_autoFree;
	};
}