#include "EC3D/GUI/Window.h"
#include "EC3D/GUI/GUIRenderer.h"

namespace ec_gui
{
	Window::Window(Widget* parent)
		: Widget(parent)
	{
	}

	Window::~Window()
	= default;

	void Window::render(GuiRenderer& renderer, GuiRenderingContext& context)
	{
		renderer.render(this, context);
	}

}