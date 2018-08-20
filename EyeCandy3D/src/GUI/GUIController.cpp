#include "EC3D/GUI/GUIController.h"
#include "EC3D/GUI/GUISystem.h"
#include "EC3D/GUI/GUI.h"
#include "EC3D/GUI/Widget.h"

#include "EC3D/Core/InputEvent.h"

#include <GLFW/glfw3.h>

namespace ec_gui
{
	GUIController::GUIController()
		: m_guiSystem{nullptr}
	{
	}

	GUIController::~GUIController()
	{
	}

	ec_gui::GUISystem* GUIController::GetGUISystem()
	{
		return m_guiSystem;
	}

	void GUIController::SetGUISystem(GUISystem* guiSystem)
	{
		m_guiSystem = guiSystem;
	}

	void GUIController::ProcessEvent(const ec::InputEvent& event)
	{
		auto* model = m_guiSystem->GetModel();

		for(auto& it : model->GetAllGUIs())
		{
			auto* widget = it->GetWidget();

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
				/// \todo implement GUIController ProcessEvent
			}
		}
	}
}