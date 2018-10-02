#pragma once
#include "Agui/Widgets/Button/ButtonListener.hpp"

#include <functional>

namespace ec
{
	class GenericButtonListener : public agui::ButtonListener
	{
	public:
		using ButtonChangedCallback_Type = std::function<void(agui::Button*, agui::Button::ButtonStateEnum)>;
		using ToggleStateChangedCallback_Type = std::function<void(agui::Button*, bool)>;
		using DeathCallback_Type = std::function<void(agui::Button*)>;
		using IsToggleButtonChangedCallback_Type = std::function<void(agui::Button*, bool)>;
		using TextAlignmentChangedCallback_Type = std::function<void(agui::Button*, agui::AreaAlignmentEnum)>;

		explicit GenericButtonListener();
		~GenericButtonListener();

		void setButtonChangedCallback(const ButtonChangedCallback_Type& callback);
		void setStateChangedCallback(const ToggleStateChangedCallback_Type& callback);
		void setDeathCallback(const DeathCallback_Type& callback);
		void setIsToggleButtonChanged(const IsToggleButtonChangedCallback_Type& callback);
		void setTextAlignmentChanged(const TextAlignmentChangedCallback_Type& callback);

		void buttonStateChanged(agui::Button* button, agui::Button::ButtonStateEnum state) override;
		void toggleStateChanged(agui::Button* button, bool down) override;
		void death(agui::Button* button) override;
		void isToggleButtonChanged(agui::Button* button, bool down) override;
		void textAlignmentChanged(agui::Button* button, agui::AreaAlignmentEnum alignment) override;

	private:
		ButtonChangedCallback_Type m_buttonChangedCb;
		ToggleStateChangedCallback_Type m_toggleStateChanged;
		DeathCallback_Type m_deathCb;
		IsToggleButtonChangedCallback_Type m_isToggleButtonChangedCb;
		TextAlignmentChangedCallback_Type m_textAlignmentChangedCb;
	};
}