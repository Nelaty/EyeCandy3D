#pragma once
#include "Widget.h"

#include <functional>

/*
* Button GUI element
* Can react on mouse button up, down and up/down events
*/
namespace ec_gui
{
	class Button : public Widget
	{
	public:
		explicit Button(Widget* parent);
		virtual ~Button();

		
		/* Set button click callbacks */
		void setOnPressedCallback(std::function<void()> callback);
		void setOnButtonDownCallback(std::function<void()> callback);
		void setOnButtonUpCallback(std::function<void()> callback);

		bool onMouseButton(const glm::ivec2& position, int button, int mods, bool pressed) override;

	protected:
		std::function<void()> m_onPressedCallback;
		std::function<void()> m_onButtonDownCallback;
		std::function<void()> m_onButtonUpCallback;
	};
}