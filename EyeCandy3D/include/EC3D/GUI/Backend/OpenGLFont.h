#pragma once
#include "Agui/BaseTypes.hpp"

namespace ec
{
	class FontTextureAtlas;
}

namespace agui
{
	class OpenGLFont : public Font
	{
	public:
		explicit OpenGLFont();
		explicit OpenGLFont(const std::string &fileName,
							int height,
							FontFlags fontFlags = FONT_DEFAULT_FLAGS,
							float borderWidth = 0,
							agui::Color borderColor = agui::Color());
		virtual ~OpenGLFont();
		
		virtual void setFont(ec::FontTextureAtlas* font, const std::string &path, bool autoFree = false);
		ec::FontTextureAtlas* getFont() const;

		virtual int getLineHeight() const override;
		virtual int getHeight() const override;
		virtual int getTextWidth(const std::string &text) const override;
		virtual const std::string& getPath() const override;

		virtual void reload(const std::string &fileName,
			int height, 
			FontFlags fontFlags = FONT_DEFAULT_FLAGS,
			float borderWidth = 0,
			agui::Color borderColor = agui::Color()) override;

		virtual void free() override;

	private:
		ec::FontTextureAtlas* font;
		std::string path;
		int height;
		int lineHeight;
		bool autoFree;
	};
}