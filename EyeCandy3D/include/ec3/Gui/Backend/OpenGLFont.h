#pragma once
#include "Agui/BaseTypes.hpp"
#include "ec3/Common/Common.h"

namespace ec
{
	class FontTextureAtlas;

	class EC3D_DECLSPEC OpenGLFont : public agui::Font
	{
	public:
		explicit OpenGLFont();
		explicit OpenGLFont(const std::string &fileName,
							int height,
		                    agui::FontFlags fontFlags = agui::FONT_DEFAULT_FLAGS,
							float borderWidth = 0,
							agui::Color borderColor = agui::Color());
		virtual ~OpenGLFont();
		
		virtual void setFont(ec::FontTextureAtlas* font, 
							 const std::string &path, 
							 bool autoFree = false);
		ec::FontTextureAtlas* getFont() const;

		int getLineHeight() const override;
		int getHeight() const override;
		int getTextWidth(const std::string &text) const override;
		const std::string& getPath() const override;

		void reload(const std::string &fileName,
					int height,
		            agui::FontFlags fontFlags = agui::FONT_DEFAULT_FLAGS,
					float borderWidth = 0,
					agui::Color borderColor = agui::Color()) override;

		void free() override;

	private:
		ec::FontTextureAtlas* font;
		std::string path;
		int height;
		int lineHeight;
		bool autoFree;
	};
}