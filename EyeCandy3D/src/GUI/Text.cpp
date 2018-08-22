#include "EC3D/Gui/Text.h"
#include "EC3D/Gui/GuiRenderer.h"

namespace ec_gui
{

	Text::Text(Widget* parent)
		: Widget(parent),
		m_textColor{0.0f, 0.0f, 0.0f, 1.0f}
	{
		setSize(0, 0);
	}

	Text::~Text()
	= default;

	void Text::render(GuiRenderer& renderer, GuiRenderingContext& context)
	{
		renderer.render(this, context);
	}

	void Text::setText(const std::string& text)
	{
		m_text = text;
	}

	void Text::setText(const int text)
	{
		m_text = std::to_string(text);
	}

	void Text::setText(const float text, const int precision)
	{
		m_text = std::to_string(text).substr(0, precision);
	}

	const std::string& Text::getText() const
	{
		return m_text;
	}

	void Text::setTextColor(const glm::vec4& color)
	{
		m_textColor = color;
	}

	const glm::vec4& Text::getTextColor() const
	{
		return m_textColor;
	}

}