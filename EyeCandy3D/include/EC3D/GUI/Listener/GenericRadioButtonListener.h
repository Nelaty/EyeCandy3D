#pragma once
#include "Agui/Widgets/RadioButton/RadioButtonListener.hpp"

#include <functional>

namespace ec
{
	class GenericRadioButtonListener : public agui::RadioButtonListener
	{
	public:
		using RadioButtonStateChanged_Callback = std::function<void(agui::RadioButton* source, agui::RadioButton::RadioButtonStateEnum state)>;
		using CheckedStateChanged_Callback = std::function<void(agui::RadioButton* source, agui::RadioButton::RadioButtonCheckedEnum state)>;
		using TextAlignmentChanged_Callback = std::function<void(agui::RadioButton* source, agui::AreaAlignmentEnum alignment)>;
		using RadioButtonAlignmentChanged_Callback = std::function<void(agui::RadioButton* source, bool autoSizing)>;
		using IsAutosizingChanged_Callback = std::function<void(agui::RadioButton* source, bool autoSizing)>;
		using Death_Callback = std::function<void(agui::RadioButton* source)>;

		explicit GenericRadioButtonListener();
		~GenericRadioButtonListener();

		void setRadioButtonStateChangedCallback(const RadioButtonStateChanged_Callback& callback);
		void setCheckedStateChangedCallback(const CheckedStateChanged_Callback& callback);
		void setTextAlignmentChangedCallback(const TextAlignmentChanged_Callback& callback);
		void setRadioButtonAlignmentCallback(const RadioButtonAlignmentChanged_Callback& callback);
		void setIsAutosizingChangedCallback(const IsAutosizingChanged_Callback& callback);
		void setDeathCallback(const Death_Callback& callback);

		void radioButtonStateChanged(agui::RadioButton* source, agui::RadioButton::RadioButtonStateEnum state) override;
		void checkedStateChanged(agui::RadioButton* source, agui::RadioButton::RadioButtonCheckedEnum state) override;
		void textAlignmentChanged(agui::RadioButton* source, agui::AreaAlignmentEnum alignment) override;
		void radioButtonAlignmentChanged(agui::RadioButton* source, agui::AreaAlignmentEnum alignment) override;
		void isAutosizingChanged(agui::RadioButton* source, bool autoSizing) override;
		void death(agui::RadioButton* source) override;
	
	private:
		RadioButtonStateChanged_Callback m_radioButtonStateChangedCb;
		CheckedStateChanged_Callback m_checkedStateChangedCb;
		TextAlignmentChanged_Callback m_textAlignmentChangedCb;
		RadioButtonAlignmentChanged_Callback m_radioButtonAlignmentChangedCb;
		IsAutosizingChanged_Callback m_isAutosizingChangedCb;
		Death_Callback m_deathCb;
	};
}