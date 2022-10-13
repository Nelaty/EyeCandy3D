#pragma once
#include "Agui/Widgets/TextBox/TextBoxListener.hpp"

#include <functional>

namespace ec
{
	/**
	 * \brief Generic gui listener that can handle events by
	 * TextBox widgets.
	 */
	class GenericTextBoxListener : public agui::TextBoxListener
	{
	public:
		using Death_Callback = std::function<void(agui::TextBox* source)>;
		using MaxLengthChanged_Callback = std::function<void(agui::TextBox* source, int maxLength)>;
		using HidingSelectionChanged_Callback = std::function<void(agui::TextBox* source, bool hiding)>;
		using StandardArrowKeyRulesChanged_Callback = std::function<void(agui::TextBox* source, bool usingStandard)>;
		using SplittingWordsChanged_Callback = std::function<void(agui::TextBox* source, bool splittingWords)>;
		using TextAppended_Callback = std::function<void(agui::TextBox* source, const std::string& appendedText)>;
		using SelectionChanged_Callback = std::function<void(agui::TextBox* source, int startIndex, int endIndex)>;
		using SelectionDeleted_Callback = std::function<void(agui::TextBox* source)>;
		using MaxCharacterSkippedChanged_Callback = std::function<void(agui::TextBox* source, int maxSkip)>;
		using ReadOnlyChanged_Callback = std::function<void(agui::TextBox* source, bool readOnly)>;
		using WordWrappedChanged_Callback = std::function<void(agui::TextBox* source, bool wordWrapped)>;

		explicit GenericTextBoxListener();
		~GenericTextBoxListener();

		void setDeathCallback(const Death_Callback& callback);
		void setMaxLengthChangedCallback(const MaxLengthChanged_Callback& callback);
		void setHidingSelectionChangedCallback(const HidingSelectionChanged_Callback& callback);
		void setStandardArrowKeyRulesChangedCallback(const StandardArrowKeyRulesChanged_Callback& callback);
		void setSplittingWordsChangedCallback(const SplittingWordsChanged_Callback& callback);
		void setTextAppendedCallback(const TextAppended_Callback& callback);
		void setSelectionChangedCallback(const SelectionChanged_Callback& callback);
		void setSelectionDeletedCallback(const SelectionDeleted_Callback& callback);
		void setMaxCharacterSkippedChangedCallback(const MaxCharacterSkippedChanged_Callback& callback);
		void setReadOnlyChangedCallback(const ReadOnlyChanged_Callback& callback);
		void setWordWrappedChangedCallback(const WordWrappedChanged_Callback& callback);

		void death(agui::TextBox* source) override;
		void maxLengthChanged(agui::TextBox* source, int maxLength) override;
		void hidingSelectionChanged(agui::TextBox* source, bool hiding) override;
		void standardArrowKeyRulesChanged(agui::TextBox* source, bool usingStandard) override;
		void splittingWordsChanged(agui::TextBox* source, bool splittingWords) override;
		void textAppended(agui::TextBox* source, const std::string& appendedText) override;
		void selectionChanged(agui::TextBox* source, int startIndex, int endIndex) override;
		void selectionDeleted(agui::TextBox* source) override;
		void maxCharacterSkippedChanged(agui::TextBox* source, int maxSkip) override;
		void readOnlyChanged(agui::TextBox* source, bool readOnly) override;
		void wordWrappedChanged(agui::TextBox* source, bool wordWrapped) override;
	
	private:
		Death_Callback m_deathCb;
		MaxLengthChanged_Callback m_maxLengthChangedCb;
		HidingSelectionChanged_Callback m_hidingSelectionChangedCb;
		StandardArrowKeyRulesChanged_Callback m_standardArrowKeyRulesChangedCb;
		SplittingWordsChanged_Callback m_splittingWordsChangedCb;
		TextAppended_Callback m_textAppendedCb;
		SelectionChanged_Callback m_selectionChangedCb;
		SelectionDeleted_Callback m_selectionDeletedCb;
		MaxCharacterSkippedChanged_Callback m_maxCharacterSkippedChangedCb;
		ReadOnlyChanged_Callback m_readOnlyChangedCb;
		WordWrappedChanged_Callback m_wordWrappedChangedCb;
	};
}