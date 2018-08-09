#pragma once
#include "Widget.h"
#include "EC3D/Core/InputEvent.h"

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
		void SetOnPressedCallback(std::function<void()> callback);
		void SetOnButtonDownCallback(std::function<void()> callback);
		void SetOnButtonUpCallback(std::function<void()> callback);

		virtual bool OnMouseButton(const glm::ivec2& position, int button, int mods, bool pressed) override;

	protected:
		std::function<void()> m_onPressedCallback;
		std::function<void()> m_onButtonDownCallback;
		std::function<void()> m_onButtonUpCallback;
	};
}