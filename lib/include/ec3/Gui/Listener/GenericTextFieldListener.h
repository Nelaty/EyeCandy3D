#pragma once
#include "Agui/Widgets/TextField/TextFieldListener.hpp"

#include <functional>

namespace ec
{
	/**
	 * \brief Generic gui listener that can handle events by
	 * TextField widgets.
	 */
	class GenericTextFieldListener : public agui::TextFieldListener
	{
	public:
		using SelectionChanged_Callback = std::function<void(agui::TextField* source, int selectionStart, int selectionEnd)>;
		using NumericChanged_Callback = std::function<void(agui::TextField* source, bool numeric, bool wantDecimal, bool wantMinus)>;
		using ReadOnlyChanged_Callback = std::function<void(agui::TextField* source, bool val)>;
		using SelectableChanged_Callback = std::function<void(agui::TextField* source, bool val)>;
		using HideSelectionChanged_Callback = std::function<void(agui::TextField* source, bool val)>;
		using Death_Callback = std::function<void(agui::TextField* source)>;

		explicit GenericTextFieldListener();
		~GenericTextFieldListener();

		void setSelectionChangedCallback(const SelectionChanged_Callback& callback);
		void setNumericChangedCallback(const NumericChanged_Callback& callback);
		void setReadOnlyChangedCallback(const ReadOnlyChanged_Callback& callback);
		void setSelectableChangedCallback(const SelectableChanged_Callback& callback);
		void setHideSelectionChangedCallback(const HideSelectionChanged_Callback& callback);
		void setDeathCallback(const Death_Callback& callback);

		void selectionChanged(agui::TextField* source, int selectionStart, int selectionEnd) override;
		void numericChanged(agui::TextField* source, bool numeric, bool wantDecimal, bool wantMinus) override;
		void readOnlyChanged(agui::TextField* source, bool val) override;
		void selectableChanged(agui::TextField* source, bool val) override;
		void hideSelectionChanged(agui::TextField* source, bool val) override;
		void death(agui::TextField* source) override;

	private:
		SelectionChanged_Callback m_selectionChangedCb;
		NumericChanged_Callback m_numericChangedCb;
		ReadOnlyChanged_Callback m_readOnlyChangedCb;
		SelectableChanged_Callback m_selectableChangedCb;
		HideSelectionChanged_Callback m_hideSelectionChangedCb;
		Death_Callback m_deathCb;
	};
}