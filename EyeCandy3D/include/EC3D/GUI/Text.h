#pragma once
#include "Widget.h"

#include <string>
#include <glm/glm.hpp>

/*
 * Widget, which holds a text string
 */

namespace ec_gui
{
	class GuiRenderer;
	class GuiRenderingContext;

	class Text : public Widget
	{
	public:
		explicit Text(Widget* parent);
		~Text();

		/* Render visitor function */
		void render(GuiRenderer& renderer, GuiRenderingContext& context) override;

		/* Text access */
		void setText(const std::string& text);
		void setText(int text);
		void setText(float text, int precision = 7);
		const std::string& getText() const;

		/* Text color access */
		void setTextColor(const glm::vec4& color);
		const glm::vec4& getTextColor() const;

	protected:
		glm::vec4 m_textColor;

		std::string m_text;
	};
}