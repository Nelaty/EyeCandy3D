#pragma once
#include "Agui/Widgets/CheckBox/CheckBoxListener.hpp"

#include <functional>

namespace ec
{
	/**
	 * \brief Generic gui listener that can handle events by CheckBox
	 * widgets.
	 */
	class GenericCheckBoxListener : public agui::CheckBoxListener
	{
	public:
		using CheckBoxStateChanged_Callback = std::function<void(agui::CheckBox* source, agui::CheckBox::CheckBoxStateEnum state)>;
		using CheckedStateChanged_Callback = std::function<void(agui::CheckBox* source, agui::CheckBox::CheckBoxCheckedEnum checked)>;
		using Death_Callback = std::function<void(agui::CheckBox* source)>;
		using TextAlignmentChanged_Callback = std::function<void(agui::CheckBox* source, agui::AreaAlignmentEnum alignment)>;
		using CheckBoxAlignmentChanged_Callback = std::function<void(agui::CheckBox* source, agui::AreaAlignmentEnum alignment)>;
		using IsAutosizingChanged_Callback = std::function<void(agui::CheckBox* source, bool autoSizing)>;
		
		explicit GenericCheckBoxListener();
		~GenericCheckBoxListener();

		void setCheckBoxStateChangedCallback(const CheckBoxStateChanged_Callback& callback);
		void setCheckedStateChangedCallback(const CheckedStateChanged_Callback& callback);
		void setDeathCallback(const Death_Callback& callback);
		void setTextAlignmentChangedCallback(const TextAlignmentChanged_Callback& callback);
		void setCheckBoxAlignmentChangedCallback(const CheckBoxAlignmentChanged_Callback& callback);
		void setIsAutosizingChangedCallback(const IsAutosizingChanged_Callback& callback);

		void checkBoxStateChanged(agui::CheckBox* source, agui::CheckBox::CheckBoxStateEnum state) override;
		void checkedStateChanged(agui::CheckBox* source, agui::CheckBox::CheckBoxCheckedEnum checked) override;
		void death(agui::CheckBox* source) override;
		void textAlignmentChanged(agui::CheckBox* source, agui::AreaAlignmentEnum alignment) override;
		void checkBoxAlignmentChanged(agui::CheckBox* source, agui::AreaAlignmentEnum alignment) override;
		void isAutosizingChanged(agui::CheckBox* source, bool autoSizing) override;
	
	private:
		CheckBoxStateChanged_Callback m_checkBoxStateChangedCb;
		CheckedStateChanged_Callback m_checkedStateChangedCb;
		Death_Callback m_deathCb;
		TextAlignmentChanged_Callback m_textAlignmentChangedCb;
		CheckBoxAlignmentChanged_Callback m_checkBoxAlignmentChangedCb;
		IsAutosizingChanged_Callback m_isAutosizingChangedCb;
	};
}