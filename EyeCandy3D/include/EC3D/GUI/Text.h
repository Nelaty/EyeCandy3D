#pragma once
#include "Widget.h"

#include <string>
#include <glm/glm.hpp>

/*
 * Widget, which holds a text string
 */

namespace ec_gui
{
	class GUIRenderer;
	class GUIRenderingContext;

	class Text : public Widget
	{
	public:
		explicit Text(Widget* parent);
		~Text();

		/* Render visitor function */
		virtual void Render(GUIRenderer& renderer, GUIRenderingContext& context) override;

		/* Text access */
		void SetText(const std::string& text);
		void SetText(int text);
		void SetText(float text, int precision = 7);
		const std::string& GetText() const;

		/* Text color access */
		void SetTextColor(const glm::vec4& color);
		const glm::vec4& GetTextColor() const;

	protected:
		glm::vec4 m_textColor;

		std::string m_text;
	};
}