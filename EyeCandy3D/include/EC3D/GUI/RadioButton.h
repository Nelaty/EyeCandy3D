#pragma once
#include "Widget.h"

#include <vector>
#include <functional>

/*
* RadioButton GUI element
* Can react on selection and de-selection callbacks
*/
namespace ec_gui
{
	class RadioButton : public Widget
	{
	public:
		explicit RadioButton(Widget* parent);
		virtual ~RadioButton();
	
		/* Selection access */
		void select();
		bool isSelected() const;

		/* Set callback, which is triggered when selecting the radio button */
		void setSelectedCallback(std::function<void()> callback);
		/* Set callback, which is triggered when another radio button is selected*/
		void setDeselectedCallback(std::function<void()> callback);

		/* Change which radio buttons are associated with each other */
		bool registerRadioButton(RadioButton* radioButton);
		bool unregisterRadioButton(RadioButton* radioButton);
		void unregisterAllRadioButtons();

		bool onMouseButton(const glm::ivec2& position, int button, int mods, bool pressed) override;

	protected:
		/* The user mustn't be allowed to deselect */
		void deselect();

	private:
		void updateDrawable();

		std::vector<RadioButton*> m_radioButtons;

		std::function<void()> m_selectedCallback = nullptr;
		std::function<void()> m_deselectedCallback = nullptr;

		bool m_selected = false;
	};
}