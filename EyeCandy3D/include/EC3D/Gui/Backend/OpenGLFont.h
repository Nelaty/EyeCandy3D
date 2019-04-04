#pragma once
#include "Agui/BaseTypes.hpp"
#include "EC3D/Common/Common.h"

namespace ec
{
	class FontTextureAtlas;

	class EC3D_DECLSPEC OpenGLFont : public agui::Font
	{
	public:
		explicit OpenGLFont();
		explicit OpenGLFont(const std::string& fileName,
							int height,
		                    agui::FontFlags fontFlags = agui::FONT_DEFAULT_FLAGS,
							float borderWidth = 0,
							agui::Color borderColor = agui::Color());
		virtual ~OpenGLFont();
		
		/** \brief Set the currently used font. */
		virtual void setFont(ec::FontTextureAtlas* font, 
							 const std::string &path, 
							 bool autoFree = false);
		
		/** \brief Get the currently used font. */
		ec::FontTextureAtlas* getFont() const;

		/** \brief Get the fonts line height. */
		int getLineHeight() const override;

		/** \brief Get the user specified height. */
		int getHeight() const override;
		
		/** \brief Get the horizontal size of a given text. */
		int getTextWidth(const std::string &text) const override;
		
		/** \brief Get the path to the font file. */
		const std::string& getPath() const override;

		/** \brief Destroy the old font and load it again. */
		void reload(const std::string &fileName,
					int height,
		            agui::FontFlags fontFlags = agui::FONT_DEFAULT_FLAGS,
					float borderWidth = 0,
					agui::Color borderColor = agui::Color()) override;

		/** \brief Destroy this font. */
		void free() override;

	private:
		
		ec::FontTextureAtlas* m_font;
		std::string m_path;
		int m_height;
		int m_lineHeight;
		bool m_autoFree;
	};
}