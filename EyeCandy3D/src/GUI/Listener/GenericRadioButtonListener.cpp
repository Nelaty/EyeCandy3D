#include "EC3D/Gui/Listener/GenericRadioButtonListener.h"

namespace ec
{
	GenericRadioButtonListener::GenericRadioButtonListener()
		: m_radioButtonStateChangedCb(nullptr),
		m_checkedStateChangedCb(nullptr),
		m_textAlignmentChangedCb(nullptr),
		m_radioButtonAlignmentChangedCb(nullptr),
		m_isAutosizingChangedCb(nullptr),
		m_deathCb(nullptr)
	{
	}

	GenericRadioButtonListener::~GenericRadioButtonListener()
	= default;

	void GenericRadioButtonListener::setRadioButtonStateChangedCallback(
		const RadioButtonStateChanged_Callback& callback)
	{
		m_radioButtonStateChangedCb = callback;
	}

	void GenericRadioButtonListener::setCheckedStateChangedCallback(const CheckedStateChanged_Callback& callback)
	{
		m_checkedStateChangedCb = callback;
	}

	void GenericRadioButtonListener::setTextAlignmentChangedCallback(const TextAlignmentChanged_Callback& callback)
	{
		m_textAlignmentChangedCb = callback;
	}

	void GenericRadioButtonListener::setRadioButtonAlignmentCallback(const RadioButtonAlignmentChanged_Callback& callback)
	{
		m_radioButtonAlignmentChangedCb = callback;
	}

	void GenericRadioButtonListener::setIsAutosizingChangedCallback(const IsAutosizingChanged_Callback& callback)
	{
		m_isAutosizingChangedCb = callback;
	}

	void GenericRadioButtonListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCb = callback;
	}

	void GenericRadioButtonListener::radioButtonStateChanged(agui::RadioButton* source,
															 const agui::RadioButton::RadioButtonStateEnum state)
	{
		if(m_radioButtonStateChangedCb)
		{
			m_radioButtonStateChangedCb(source, state);
		}
	}

	void GenericRadioButtonListener::checkedStateChanged(agui::RadioButton* source,
														 const agui::RadioButton::RadioButtonCheckedEnum state)
	{
		if(m_checkedStateChangedCb)
		{
			m_checkedStateChangedCb(source, state);
		}
	}

	void GenericRadioButtonListener::textAlignmentChanged(agui::RadioButton* source, 
														  const agui::AreaAlignmentEnum alignment)
	{
		if(m_textAlignmentChangedCb)
		{
			m_textAlignmentChangedCb(source, alignment);
		}
	}

	void GenericRadioButtonListener::radioButtonAlignmentChanged(agui::RadioButton* source,
																 const agui::AreaAlignmentEnum alignment)
	{
		if(m_radioButtonAlignmentChangedCb)
		{
			m_radioButtonAlignmentChangedCb(source, alignment);
		}
	}

	void GenericRadioButtonListener::isAutosizingChanged(agui::RadioButton* source,
														 const bool autoSizing)
	{
		if(m_isAutosizingChangedCb)
		{
			m_isAutosizingChangedCb(source, autoSizing);
		}
	}

	void GenericRadioButtonListener::death(agui::RadioButton* source)
	{
		if(m_deathCb)
		{
			m_deathCb(source);
		}
	}
}
