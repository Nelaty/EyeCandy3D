#pragma once
#include "Agui/Widgets/Button/ButtonListener.hpp"

#include <functional>

namespace ec
{
	class GenericButtonListener : public agui::ButtonListener
	{
	public:
		using ButtonChanged_Callback = std::function<void(agui::Button* source, agui::Button::ButtonStateEnum state)>;
		using ToggleStateChanged_Callback = std::function<void(agui::Button* source, bool down)>;
		using Death_Callback = std::function<void(agui::Button* source)>;
		using IsToggleButtonChanged_Callback = std::function<void(agui::Button* source, bool down)>;
		using TextAlignmentChanged_Callback = std::function<void(agui::Button* source, agui::AreaAlignmentEnum alignment)>;

		explicit GenericButtonListener();
		~GenericButtonListener();

		void setButtonChangedCallback(const ButtonChanged_Callback& callback);
		void setStateChangedCallback(const ToggleStateChanged_Callback& callback);
		void setDeathCallback(const Death_Callback& callback);
		void setIsToggleButtonChanged(const IsToggleButtonChanged_Callback& callback);
		void setTextAlignmentChanged(const TextAlignmentChanged_Callback& callback);

		void buttonStateChanged(agui::Button* source, agui::Button::ButtonStateEnum state) override;
		void toggleStateChanged(agui::Button* source, bool down) override;
		void death(agui::Button* source) override;
		void isToggleButtonChanged(agui::Button* source, bool down) override;
		void textAlignmentChanged(agui::Button* source, agui::AreaAlignmentEnum alignment) override;

	private:
		ButtonChanged_Callback m_buttonChangedCb;
		ToggleStateChanged_Callback m_toggleStateChanged;
		Death_Callback m_deathCb;
		IsToggleButtonChanged_Callback m_isToggleButtonChangedCb;
		TextAlignmentChanged_Callback m_textAlignmentChangedCb;
	};
}