#include "EC3D/GUI/Window.h"
#include "EC3D/GUI/GUIRenderer.h"

namespace ec_gui
{
	Window::Window(Widget* parent)
		: Widget(parent)
	{
	}

	Window::~Window()
	{
	}

	void Window::Render(GUIRenderer& renderer, GUIRenderingContext& context)
	{
		renderer.Render(this, context);
	}

}