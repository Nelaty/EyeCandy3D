#pragma once
#include "Widget.h"

/*
* Window GUI element
* Can be moved via drag and drop.
*/
namespace ec_gui
{
	class GUIRenderer;
	class GUIRenderingContext;

	class Window : public Widget
	{
	public:
		explicit Window(Widget* parent);
		virtual ~Window();

		/* Render visitor function */
		virtual void Render(GUIRenderer& renderer, GUIRenderingContext& context) override;

	private:

	};
}