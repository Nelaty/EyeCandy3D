#include "EC3D/GUI/Button.h"

#include "EC3D/Core/Drawable.h"

namespace ec_gui
{
	Button::Button(Widget* parent)
		: Widget(parent),
		m_onPressedCallback{nullptr},
		m_onButtonDownCallback{nullptr},
		m_onButtonUpCallback{nullptr}
	{
	}

	Button::~Button()
	{
	}

	void Button::SetOnPressedCallback(std::function<void()> callback)
	{
		m_onPressedCallback = callback;
	}

	void Button::SetOnButtonDownCallback(std::function<void()> callback)
	{
		m_onButtonDownCallback = callback;
	}

	void Button::SetOnButtonUpCallback(std::function<void()> callback)
	{
		m_onButtonUpCallback = callback;
	}

	bool Button::OnMouseButton(const glm::ivec2& position, int button, int mods, bool pressed)
	{
		if(__super::OnMouseButton(position, button, mods, pressed))
		{
			return true;
		}

		if(Contains(position))
		{
			if(m_onPressedCallback)	m_onPressedCallback();
			if(pressed)
			{
				if(m_onButtonDownCallback) m_onButtonDownCallback();
			}
			else
			{
				if(m_onButtonUpCallback) m_onButtonUpCallback();
			}
			return true;
		}
		return false;
	}
}