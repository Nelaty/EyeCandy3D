#include "EC3D/GUI/Text.h"
#include "EC3D/GUI/GUIRenderer.h"

namespace ec_gui
{

	Text::Text(Widget* parent)
		: Widget(parent),
		m_textColor{0.0f, 0.0f, 0.0f, 1.0f}
	{
		SetSize(0, 0);
	}

	Text::~Text()
	{
	}

	void Text::Render(GUIRenderer& renderer, GUIRenderingContext& context)
	{
		renderer.Render(this, context);
	}

	void Text::SetText(const std::string& text)
	{
		m_text = text;
	}

	void Text::SetText(int text)
	{
		m_text = std::to_string(text);
	}

	void Text::SetText(float text, int precision /*= 7*/)
	{
		m_text = std::to_string(text).substr(0, precision);
	}

	const std::string& Text::GetText() const
	{
		return m_text;
	}

	void Text::SetTextColor(const glm::vec4& color)
	{
		m_textColor = color;
	}

	const glm::vec4& Text::GetTextColor() const
	{
		return m_textColor;
	}

}