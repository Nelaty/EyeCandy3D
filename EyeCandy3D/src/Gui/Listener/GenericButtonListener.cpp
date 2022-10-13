#include "ec3/Gui/Listener/GenericButtonListener.h"

namespace ec
{
	GenericButtonListener::GenericButtonListener()
		: m_buttonChangedCb(nullptr),
		m_toggleStateChanged(nullptr),
		m_deathCb(nullptr),
		m_isToggleButtonChangedCb(nullptr),
		m_textAlignmentChangedCb(nullptr)
	{
	}

	GenericButtonListener::~GenericButtonListener()
	= default;

	void GenericButtonListener::setButtonChangedCallback(const ButtonChanged_Callback& callback)
	{
		m_buttonChangedCb = callback;
	}

	void GenericButtonListener::setStateChangedCallback(const ToggleStateChanged_Callback& callback)
	{
		m_toggleStateChanged = callback;
	}

	void GenericButtonListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCb = callback;
	}

	void GenericButtonListener::setIsToggleButtonChanged(const IsToggleButtonChanged_Callback& callback)
	{
		m_isToggleButtonChangedCb = callback;
	}

	void GenericButtonListener::setTextAlignmentChanged(const TextAlignmentChanged_Callback& callback)
	{
		m_textAlignmentChangedCb = callback;
	}

	void GenericButtonListener::buttonStateChanged(agui::Button* source,
												   const agui::Button::ButtonStateEnum state)
	{
		if(m_buttonChangedCb)
		{
			m_buttonChangedCb(source, state);
		}
	}

	void GenericButtonListener::toggleStateChanged(agui::Button* source, 
												   const bool down)
	{
		if(m_toggleStateChanged)
		{
			m_toggleStateChanged(source, down);
		}
	}

	void GenericButtonListener::death(agui::Button* source)
	{
		if(m_deathCb)
		{
			m_deathCb(source);
		}
	}

	void GenericButtonListener::isToggleButtonChanged(agui::Button* source,
													  const bool down)
	{
		if(m_isToggleButtonChangedCb)
		{
			m_isToggleButtonChangedCb(source, down);
		}
	}

	void GenericButtonListener::textAlignmentChanged(agui::Button* source, 
													 const agui::AreaAlignmentEnum alignment)
	{
		if(m_textAlignmentChangedCb)
		{
			m_textAlignmentChangedCb(source, alignment);
		}
	}
}