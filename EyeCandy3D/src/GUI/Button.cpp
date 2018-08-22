#include <utility>
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
	= default;

	void Button::setOnPressedCallback(std::function<void()> callback)
	{
		m_onPressedCallback = std::move(callback);
	}

	void Button::setOnButtonDownCallback(std::function<void()> callback)
	{
		m_onButtonDownCallback = std::move(callback);
	}

	void Button::setOnButtonUpCallback(std::function<void()> callback)
	{
		m_onButtonUpCallback = std::move(callback);
	}

	bool Button::onMouseButton(const glm::ivec2& position, int button, int mods, bool pressed)
	{
		if(__super::onMouseButton(position, button, mods, pressed))
		{
			return true;
		}

		if(contains(position))
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