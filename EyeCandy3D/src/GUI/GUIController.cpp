#include "EC3D/GUI/GuiController.h"
#include "EC3D/GUI/GuiSystem.h"
#include "EC3D/GUI/Gui.h"
#include "EC3D/GUI/Widget.h"

#include "EC3D/Core/InputEvent.h"

#include <GLFW/glfw3.h>

namespace ec_gui
{
	GuiController::GuiController()
		: m_guiSystem{nullptr}
	{
	}

	GuiController::~GuiController()
	= default;

	ec_gui::GuiSystem* GuiController::getGuiSystem() const
	{
		return m_guiSystem;
	}

	void GuiController::setGuiSystem(GuiSystem* guiSystem)
	{
		m_guiSystem = guiSystem;
	}

	void GuiController::processEvent(const ec::InputEvent& event)
	{
		auto* model = m_guiSystem->getModel();

		for(auto& it : model->getAllGuIs())
		{
			auto* widget = it->getWidget();

			auto CursorPos = [](GLFWwindow* window)
			{
				double x;
				double y;
				glfwGetCursorPos(window, &x, &y);
				return glm::ivec2(static_cast<int>(x), static_cast<int>(y));
			};

			// Don't send an event type object from the scene graph as a parameter
			// to make the GUI more light weight.
			switch(event.m_type)
			{
				/// \todo implement GuiController ProcessEvent
			}
		}
	}
}