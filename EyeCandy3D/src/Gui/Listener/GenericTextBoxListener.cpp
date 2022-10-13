#include "ec3/Gui/Listener/GenericTextBoxListener.h"

namespace ec
{
	GenericTextBoxListener::GenericTextBoxListener()
		: m_deathCb(nullptr),
		m_maxLengthChangedCb(nullptr),
		m_hidingSelectionChangedCb(nullptr),
		m_standardArrowKeyRulesChangedCb(nullptr),
		m_splittingWordsChangedCb(nullptr),
		m_textAppendedCb(nullptr),
		m_selectionChangedCb(nullptr),
		m_selectionDeletedCb(nullptr),
		m_maxCharacterSkippedChangedCb(nullptr),
		m_readOnlyChangedCb(nullptr),
		m_wordWrappedChangedCb(nullptr)
	{
	}

	GenericTextBoxListener::~GenericTextBoxListener()
	= default;

	void GenericTextBoxListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCb = callback;
	}

	void GenericTextBoxListener::setMaxLengthChangedCallback(const MaxLengthChanged_Callback& callback)
	{
		m_maxLengthChangedCb = callback;
	}

	void GenericTextBoxListener::setHidingSelectionChangedCallback(const HidingSelectionChanged_Callback& callback)
	{
		m_hidingSelectionChangedCb = callback;
	}

	void GenericTextBoxListener::setStandardArrowKeyRulesChangedCallback(const StandardArrowKeyRulesChanged_Callback& callback)
	{
		m_standardArrowKeyRulesChangedCb = callback;
	}

	void GenericTextBoxListener::setSplittingWordsChangedCallback(const SplittingWordsChanged_Callback& callback)
	{
		m_splittingWordsChangedCb = callback;
	}

	void GenericTextBoxListener::setTextAppendedCallback(const TextAppended_Callback& callback)
	{
		m_textAppendedCb = callback;
	}

	void GenericTextBoxListener::setSelectionChangedCallback(const SelectionChanged_Callback& callback)
	{
		m_selectionChangedCb = callback;
	}

	void GenericTextBoxListener::setSelectionDeletedCallback(const SelectionDeleted_Callback& callback)
	{
		m_selectionDeletedCb = callback;
	}

	void GenericTextBoxListener::setMaxCharacterSkippedChangedCallback(const MaxCharacterSkippedChanged_Callback& callback)
	{
		m_maxCharacterSkippedChangedCb = callback;
	}

	void GenericTextBoxListener::setReadOnlyChangedCallback(const ReadOnlyChanged_Callback& callback)
	{
		m_readOnlyChangedCb = callback;
	}

	void GenericTextBoxListener::setWordWrappedChangedCallback(const WordWrappedChanged_Callback& callback)
	{
		m_wordWrappedChangedCb = callback;
	}

	void GenericTextBoxListener::death(agui::TextBox* source)
	{
		if(m_deathCb)
		{
			m_deathCb(source);
		}
	}

	void GenericTextBoxListener::maxLengthChanged(agui::TextBox* source, 
												  const int maxLength)
	{
		if(m_maxLengthChangedCb)
		{
			m_maxLengthChangedCb(source, maxLength);
		}
	}

	void GenericTextBoxListener::hidingSelectionChanged(agui::TextBox* source, 
														const bool hiding)
	{
		if(m_hidingSelectionChangedCb)
		{
			m_hidingSelectionChangedCb(source, hiding);
		}
	}

	void GenericTextBoxListener::standardArrowKeyRulesChanged(agui::TextBox* source, 
															  const bool usingStandard)
	{
		if(m_standardArrowKeyRulesChangedCb)
		{
			m_standardArrowKeyRulesChangedCb(source, usingStandard);
		}
	}

	void GenericTextBoxListener::splittingWordsChanged(agui::TextBox* source,
													   const bool splittingWords)
	{
		if(m_splittingWordsChangedCb)
		{
			m_splittingWordsChangedCb(source, splittingWords);
		}
	}

	void GenericTextBoxListener::textAppended(agui::TextBox* source,
											  const std::string& appendedText)
	{
		if(m_textAppendedCb)
		{
			m_textAppendedCb(source, appendedText);
		}
	}

	void GenericTextBoxListener::selectionChanged(agui::TextBox* source, 
												  const int startIndex, 
												  const int endIndex)
	{
		if(m_selectionChangedCb)
		{
			m_selectionChangedCb(source, startIndex, endIndex);
		}
	}

	void GenericTextBoxListener::selectionDeleted(agui::TextBox* source)
	{
		if(m_selectionDeletedCb)
		{
			m_selectionDeletedCb(source);
		}
	}

	void GenericTextBoxListener::maxCharacterSkippedChanged(agui::TextBox* source, 
															const int maxSkip)
	{
		if(m_maxCharacterSkippedChangedCb)
		{
			m_maxCharacterSkippedChangedCb(source, maxSkip);
		}
	}

	void GenericTextBoxListener::readOnlyChanged(agui::TextBox* source, 
												 const bool readOnly)
	{
		if(m_readOnlyChangedCb)
		{
			m_readOnlyChangedCb(source, readOnly);
		}
	}

	void GenericTextBoxListener::wordWrappedChanged(agui::TextBox* source, 
													const bool wordWrapped)
	{
		if(m_wordWrappedChangedCb)
		{
			m_wordWrappedChangedCb(source, wordWrapped);
		}
	}
}