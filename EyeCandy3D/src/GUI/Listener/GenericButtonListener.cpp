#include "EC3D/Gui/Listener/GenericButtonListener.h"

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

	void GenericButtonListener::setButtonChangedCallback(const ButtonChangedCallback_Type& callback)
	{
		m_buttonChangedCb = callback;
	}

	void GenericButtonListener::setStateChangedCallback(const ToggleStateChangedCallback_Type& callback)
	{
		m_toggleStateChanged = callback;
	}

	void GenericButtonListener::setDeathCallback(const DeathCallback_Type& callback)
	{
		m_deathCb = callback;
	}

	void GenericButtonListener::setIsToggleButtonChanged(const IsToggleButtonChangedCallback_Type& callback)
	{
		m_isToggleButtonChangedCb = callback;
	}

	void GenericButtonListener::setTextAlignmentChanged(const TextAlignmentChangedCallback_Type& callback)
	{
		m_textAlignmentChangedCb = callback;
	}

	void GenericButtonListener::buttonStateChanged(agui::Button* button, agui::Button::ButtonStateEnum state)
	{
		if(m_buttonChangedCb)
		{
			m_buttonChangedCb(button, state);
		}
	}

	void GenericButtonListener::toggleStateChanged(agui::Button* button, bool down)
	{
		if(m_toggleStateChanged)
		{
			m_toggleStateChanged(button, down);
		}
	}

	void GenericButtonListener::death(agui::Button* button)
	{
		if(m_deathCb)
		{
			m_deathCb(button);
		}
	}

	void GenericButtonListener::isToggleButtonChanged(agui::Button* button, bool down)
	{
		if(m_isToggleButtonChangedCb)
		{
			m_isToggleButtonChangedCb(button, down);
		}
	}

	void GenericButtonListener::textAlignmentChanged(agui::Button* button, agui::AreaAlignmentEnum alignment)
	{
		if(m_textAlignmentChangedCb)
		{
			m_textAlignmentChangedCb(button, alignment);
		}
	}
}