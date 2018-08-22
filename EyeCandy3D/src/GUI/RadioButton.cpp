#include "EC3D/GUI/RadioButton.h"
#include "EC3D/GUI/Theme.h"

#include <algorithm>
#include <iterator>
#include <utility>

namespace ec_gui
{
	RadioButton::RadioButton(Widget* parent)
		: Widget(parent)
	{
		updateDrawable();
	}

	RadioButton::~RadioButton()
	= default;

	void RadioButton::select()
	{
		if(m_selected) return;

		m_selected = true;
		if(m_selectedCallback)
		{
			m_selectedCallback();
		}
		updateDrawable();

		// Deselect all but the active radio button
		for(auto& it : m_radioButtons)
		{
			it->deselect();
		}
	}

	bool RadioButton::isSelected() const
	{
		return m_selected;
	}

	void RadioButton::setSelectedCallback(std::function<void()> callback)
	{
		m_selectedCallback = std::move(callback);
	}

	void RadioButton::setDeselectedCallback(std::function<void()> callback)
	{
		m_deselectedCallback = std::move(callback);
	}

	bool RadioButton::registerRadioButton(RadioButton* radioButton)
	{
		// Radio buttons can't be registered at themselves
		if(radioButton == this) return false;

		// Check if the given radio button is already registered
		auto isNew = true;
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
			radioButton->registerRadioButton(this);
			for(const auto& it : m_radioButtons)
			{
				radioButton->registerRadioButton(it);
			}
		}

		return isNew;
	}

	bool RadioButton::unregisterRadioButton(RadioButton* radioButton)
	{
		const auto foundButton = std::remove(m_radioButtons.begin(), m_radioButtons.end(), radioButton);
		const auto removed = foundButton != m_radioButtons.end();

		if(removed)
		{
			radioButton->unregisterAllRadioButtons();
		}

		return removed;
	}

	void RadioButton::unregisterAllRadioButtons()
	{
		m_radioButtons.clear();
	}

	bool RadioButton::onMouseButton(const glm::ivec2& position, int button, int mods, bool pressed)
	{
		if(!pressed) return false;

		if(Widget::onMouseButton(position, button, mods, pressed))
		{
			return true;
		}

		if(contains(position) && !m_selected)
		{
			select();
			return true;
		}
		return false;
	}

	void RadioButton::deselect()
	{
		if(!m_selected) return;

		m_selected = false;
		if(m_deselectedCallback)
		{
			m_deselectedCallback();
		}
		updateDrawable();
	}

	void RadioButton::updateDrawable()
	{
		if(s_theme)
		{
			if(m_selected)
			{
				setDrawable(s_theme->m_radioButtonOn.get());
			}
			else
			{
				setDrawable(s_theme->m_radioButtonOff.get());
			}
		}
	}

}