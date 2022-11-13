#include "ec3/Gui/Listener/GenericCheckBoxListener.h"

namespace ec
{
	GenericCheckBoxListener::GenericCheckBoxListener()
		: m_checkBoxStateChangedCb(nullptr),
		  m_checkedStateChangedCb(nullptr),
		  m_deathCb(nullptr),
		  m_textAlignmentChangedCb(nullptr),
		  m_checkBoxAlignmentChangedCb(nullptr),
		  m_isAutosizingChangedCb(nullptr)
	{
	}

	GenericCheckBoxListener::~GenericCheckBoxListener()
	= default;

	void GenericCheckBoxListener::setCheckBoxStateChangedCallback(const CheckBoxStateChanged_Callback& callback)
	{
		m_checkBoxStateChangedCb = callback;
	}

	void GenericCheckBoxListener::setCheckedStateChangedCallback(const CheckedStateChanged_Callback& callback)
	{
		m_checkedStateChangedCb = callback;
	}

	void GenericCheckBoxListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCb = callback;
	}

	void GenericCheckBoxListener::setTextAlignmentChangedCallback(const TextAlignmentChanged_Callback& callback)
	{
		m_textAlignmentChangedCb = callback;
	}

	void GenericCheckBoxListener::setCheckBoxAlignmentChangedCallback(const CheckBoxAlignmentChanged_Callback& callback)
	{
		m_checkBoxAlignmentChangedCb = callback;
	}

	void GenericCheckBoxListener::setIsAutosizingChangedCallback(const IsAutosizingChanged_Callback& callback)
	{
		m_isAutosizingChangedCb = callback;
	}

	void GenericCheckBoxListener::checkBoxStateChanged(agui::CheckBox* source,
	                                                   const agui::CheckBox::CheckBoxStateEnum state)
	{
		if (m_checkBoxStateChangedCb)
		{
			m_checkBoxStateChangedCb(source, state);
		}
	}

	void GenericCheckBoxListener::checkedStateChanged(agui::CheckBox* source,
	                                                  const agui::CheckBox::CheckBoxCheckedEnum checked)
	{
		if (m_checkedStateChangedCb)
		{
			m_checkedStateChangedCb(source, checked);
		}	
	}

	void GenericCheckBoxListener::death(agui::CheckBox* source)
	{
		if(m_deathCb)
		{
			m_deathCb(source);
		}
	}

	void GenericCheckBoxListener::textAlignmentChanged(agui::CheckBox* source,
	                                                   const agui::AreaAlignmentEnum alignment)
	{
		if(m_textAlignmentChangedCb)
		{
			m_textAlignmentChangedCb(source, alignment);
		}
	}

	void GenericCheckBoxListener::checkBoxAlignmentChanged(agui::CheckBox* source,
	                                                       const agui::AreaAlignmentEnum alignment)
	{
		if(m_checkBoxAlignmentChangedCb)
		{
			m_checkBoxAlignmentChangedCb(source, alignment);
		}
	}

	void GenericCheckBoxListener::isAutosizingChanged(agui::CheckBox* source,
	                                                  const bool autoSizing)
	{
		if(m_isAutosizingChangedCb)
		{
			m_isAutosizingChangedCb(source, autoSizing);
		}
	}
}
