#pragma once
#include "Agui/BaseTypes.hpp"
#include "ec3/Common/Common.h"

#include "ec3/Graphics/Material/Texture.h"

namespace ec
{
	/** OpenGL back end for images used by Agui */
	class EC3D_DECLSPEC OpenGLImage : public agui::Image
	{		
	public:
		explicit OpenGLImage();
		explicit OpenGLImage(const std::string& fileName, bool convertMask = false);
		virtual ~OpenGLImage();
		
		/** Get the width of the texture in pixels. */
		int getWidth() const override;
		/** Get the height of the texture in pixels. */
		int getHeight() const override;
		
		/** Get the color of a pixel at a given position */
		agui::Color getPixel(int x, int y) const override;
		/** Set a pixel of the texture at a given position */
		void setPixel(int x, int y, const agui::Color& color) override;
		
		/** Set the texture to a given one. */
		void setTexture(const ec::Texture& texture, bool autoFree = false);
		/** Get the current texture. */
		const ec::Texture& getTexture() const;
		
		/** Check if the texture gets automatically deallocated */
		bool isAutoFreeing() const override;
		/** Free memory allocated by the texture */
		void free() override;
		
	private:
		ec::Texture m_texture;

		bool m_autoFree = false;
	};
}