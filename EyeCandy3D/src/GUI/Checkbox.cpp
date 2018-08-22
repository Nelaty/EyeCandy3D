#include <utility>
#include "EC3D/GUI/Checkbox.h"
#include "EC3D/GUI/Theme.h"

namespace ec_gui
{
	Checkbox::Checkbox(Widget* parent)
		: Widget(parent),
		m_selected{false}
	{
		updateDrawable();
	}

	Checkbox::~Checkbox()
	= default;

	void Checkbox::setSelectedCallback(std::function<void()> callback)
	{
		m_selectedCallback = std::move(callback);
	}

	void Checkbox::setDeselectedCallback(std::function<void()> callback)
	{
		m_deselectedCallback = std::move(callback);
	}

	void Checkbox::select(const bool selected)
	{
		if(m_selected == selected) return;
		m_selected = selected;
		updateDrawable();

		if(m_selected && m_selectedCallback)
		{
			m_selectedCallback();
		}
		else if(m_deselectedCallback)
		{
			m_deselectedCallback();
		}
	}

	void Checkbox::toggleSelection()
	{
		select(!m_selected);
	}

	bool Checkbox::isSelected() const
	{
		return m_selected;
	}

	bool Checkbox::onMouseButton(const glm::ivec2& position, int button, int mods, bool pressed)
	{
		if(!pressed) return false;

		if(Widget::onMouseButton(position, button, mods, pressed))
		{
			return true;
		}

		if(contains(position))
		{
			toggleSelection();
			return true;
		}
		return false;
	}

	void Checkbox::updateDrawable()
	{
		if(s_theme)
		{
			if(m_selected)
			{
				setDrawable(s_theme->m_checkboxOn.get());
			}
			else
			{
				setDrawable(s_theme->m_checkboxOff.get());
			}
		}
	}

}