#include "EC3D/GUI/Checkbox.h"
#include "EC3D/GUI/Theme.h"

namespace ec_gui
{
	Checkbox::Checkbox(Widget* parent)
		: Widget(parent),
		m_selected{false}
	{
		UpdateDrawable();
	}

	Checkbox::~Checkbox()
	{
	}

	void Checkbox::SetSelectedCallback(std::function<void()> callback)
	{
		m_selectedCallback = callback;
	}

	void Checkbox::SetDeselectedCallback(std::function<void()> callback)
	{
		m_deselectedCallback = callback;
	}

	void Checkbox::Select(const bool selected)
	{
		if(m_selected == selected) return;
		m_selected = selected;
		UpdateDrawable();

		if(m_selected && m_selectedCallback)
		{
			m_selectedCallback();
		}
		else if(m_deselectedCallback)
		{
			m_deselectedCallback();
		}
	}

	void Checkbox::ToggleSelection()
	{
		Select(!m_selected);
	}

	bool Checkbox::IsSelected() const
	{
		return m_selected;
	}

	bool Checkbox::OnMouseButton(const glm::ivec2& position, int button, int mods, bool pressed)
	{
		if(!pressed) return false;

		if(Widget::OnMouseButton(position, button, mods, pressed))
		{
			return true;
		}

		if(Contains(position))
		{
			ToggleSelection();
			return true;
		}
		return false;
	}

	void Checkbox::UpdateDrawable()
	{
		if(s_theme)
		{
			if(m_selected)
			{
				SetDrawable(s_theme->m_checkboxOn.get());
			}
			else
			{
				SetDrawable(s_theme->m_checkboxOff.get());
			}
		}
	}

}