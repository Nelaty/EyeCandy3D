#pragma once
#include "Widget.h"

#include <vector>
#include <functional>

/*
* RadioButton GUI element
* Can react on selection and deselection callbacks
*/
namespace ec_gui
{
	class RadioButton : public Widget
	{
	public:
		explicit RadioButton(Widget* parent);
		virtual ~RadioButton();
	
		/* Selection access */
		void Select();
		bool IsSelected() const;

		/* Set callback, which is triggered when selecting the radio button */
		void SetSelectedCallback(std::function<void()> callback);
		/* Set callback, which is triggered when another radio button is selected*/
		void SetDeselectedCallback(std::function<void()> callback);

		/* Change which radio buttons are associated with each other */
		bool RegisterRadioButton(RadioButton* radioButton);
		bool UnregisterRadioButton(RadioButton* radioButton);
		void UnregisterAllRadioButtons();

		virtual bool OnMouseButton(const glm::ivec2& position, int button, int mods, bool pressed) override;

	protected:
		/* The user mustn't be allowed to deselect */
		void Deselect();

	private:
		void UpdateDrawable();

		std::vector<RadioButton*> m_radioButtons;

		std::function<void()> m_selectedCallback;
		std::function<void()> m_deselectedCallback;

		bool m_selected;
	};
}