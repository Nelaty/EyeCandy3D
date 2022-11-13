#include "ec3/Gui/Listener/GenericTextFieldListener.h"

namespace ec
{
	GenericTextFieldListener::GenericTextFieldListener()
		: m_selectionChangedCb(nullptr),
		m_numericChangedCb(nullptr),
		m_readOnlyChangedCb(nullptr),
		m_selectableChangedCb(nullptr),
		m_hideSelectionChangedCb(nullptr),
		m_deathCb(nullptr)
	{
	}

	GenericTextFieldListener::~GenericTextFieldListener()
	= default;

	void GenericTextFieldListener::setSelectionChangedCallback(const SelectionChanged_Callback& callback)
	{
		m_selectionChangedCb = callback;
	}

	void GenericTextFieldListener::setNumericChangedCallback(const NumericChanged_Callback& callback)
	{
		m_numericChangedCb = callback;
	}

	void GenericTextFieldListener::setReadOnlyChangedCallback(const ReadOnlyChanged_Callback& callback)
	{
		m_readOnlyChangedCb = callback;
	}

	void GenericTextFieldListener::setSelectableChangedCallback(const SelectableChanged_Callback& callback)
	{
		m_selectableChangedCb = callback;
	}

	void GenericTextFieldListener::setHideSelectionChangedCallback(const HideSelectionChanged_Callback& callback)
	{
		m_hideSelectionChangedCb = callback;
	}

	void GenericTextFieldListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCb = callback;
	}

	void GenericTextFieldListener::selectionChanged(agui::TextField* source, 
													const int selectionStart, 
													const int selectionEnd)
	{
		if(m_selectionChangedCb)
		{
			m_selectionChangedCb(source, selectionStart, selectionEnd);
		}
	}

	void GenericTextFieldListener::numericChanged(agui::TextField* source, 
												  const bool numeric, 
												  const bool wantDecimal,
		bool wantMinus)
	{
		if(m_numericChangedCb)
		{
			m_numericChangedCb(source, numeric, wantDecimal, wantMinus);
		}
	}

	void GenericTextFieldListener::readOnlyChanged(agui::TextField* source,
												   const bool val)
	{
		if(m_readOnlyChangedCb)
		{
			m_readOnlyChangedCb(source, val);
		}
	}

	void GenericTextFieldListener::selectableChanged(agui::TextField* source, 
													 const bool val)
	{
		if(m_selectableChangedCb)
		{
			m_selectableChangedCb(source, val);
		}
	}

	void GenericTextFieldListener::hideSelectionChanged(agui::TextField* source, 
														const bool val)
	{
		if(m_hideSelectionChangedCb)
		{
			m_hideSelectionChangedCb(source, val);
		}
	}

	void GenericTextFieldListener::death(agui::TextField* source)
	{
		if(m_deathCb)
		{
			m_deathCb(source);
		}
	}
}