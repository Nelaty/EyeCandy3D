#include "EC3D/GUI/RadioButton.h"
#include "EC3D/GUI/Theme.h"

#include <algorithm>
#include <iterator>

namespace ec_gui
{
	RadioButton::RadioButton(Widget* parent)
		: Widget(parent),
		m_selected{false},
		m_selectedCallback{nullptr},
		m_deselectedCallback{nullptr}
	{
		UpdateDrawable();
	}

	RadioButton::~RadioButton()
	{
	}

	void RadioButton::Select()
	{
		if(m_selected) return;

		m_selected = true;
		if(m_selectedCallback)
		{
			m_selectedCallback();
		}
		UpdateDrawable();

		// Deselect all but the active radio button
		for(auto& it : m_radioButtons)
		{
			it->Deselect();
		}
	}

	bool RadioButton::IsSelected() const
	{
		return m_selected;
	}

	void RadioButton::SetSelectedCallback(std::function<void()> callback)
	{
		m_selectedCallback = callback;
	}

	void RadioButton::SetDeselectedCallback(std::function<void()> callback)
	{
		m_deselectedCallback = callback;
	}

	bool RadioButton::RegisterRadioButton(RadioButton* radioButton)
	{
		// Radio buttons can't be registered at themselves
		if(radioButton == this) return false;

		// Check if the given radio button is already registered
		bool isNew = true;
		for(const auto& it : m_radioButtons)
		{
			if(it == radioButton)
			{
				isNew = false;
				break;
			}
		}

		// Register the given radio button if it isn't already
		if(isNew)
		{
			m_radioButtons.push_back(radioButton);
			radioButton->RegisterRadioButton(this);
			for(const auto& it : m_radioButtons)
			{
				radioButton->RegisterRadioButton(it);
			}
		}

		return isNew;
	}

	bool RadioButton::UnregisterRadioButton(RadioButton* radioButton)
	{
		auto foundButton = std::remove(m_radioButtons.begin(), m_radioButtons.end(), radioButton);
		bool removed = foundButton != m_radioButtons.end();

		if(removed)
		{
			radioButton->UnregisterAllRadioButtons();
		}

		return removed;
	}

	void RadioButton::UnregisterAllRadioButtons()
	{
		m_radioButtons.clear();
	}

	bool RadioButton::OnMouseButton(const glm::ivec2& position, int button, int mods, bool pressed)
	{
		if(!pressed) return false;

		if(Widget::OnMouseButton(position, button, mods, pressed))
		{
			return true;
		}

		if(Contains(position) && !m_selected)
		{
			Select();
			return true;
		}
		return false;
	}

	void RadioButton::Deselect()
	{
		if(!m_selected) return;

		m_selected = false;
		if(m_deselectedCallback)
		{
			m_deselectedCallback();
		}
		UpdateDrawable();
	}

	void RadioButton::UpdateDrawable()
	{
		if(s_theme)
		{
			if(m_selected)
			{
				SetDrawable(s_theme->m_radioButtonOn.get());
			}
			else
			{
				SetDrawable(s_theme->m_radioButtonOff.get());
			}
		}
	}

}