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
				case ec::InputType::mouse_button_pressed:
				case ec::InputType::mouse_button_released:
				{
					const auto& e = event.m_event.m_mouse;
					widget->OnMouseButton(CursorPos(e.m_window), e.m_button, e.m_mods, e.m_pressed);
					break;
				}
				case ec::InputType::mouse_move:
				{
					const auto& e = event.m_event.m_move;
					widget->OnMouseMove(glm::ivec2(static_cast<int>(e.m_x), static_cast<int>(e.m_y)));
					break;
				}
				case ec::InputType::mouse_drag:
				{
					const auto& e = event.m_event.m_drag;
					widget->OnMouseDrag(glm::ivec2(static_cast<int>(e.m_x), static_cast<int>(e.m_y)),
										glm::ivec2(static_cast<int>(e.m_offsetX), static_cast<int>(e.m_offsetY)),
										e.m_button, e.m_modifier);
					break;
				}
				case ec::InputType::mouse_scroll:
				{
					const auto& e = event.m_event.m_move;
					widget->OnMouseScroll(CursorPos(e.m_window), glm::vec2(e.m_x, e.m_y));
					break;
				}
				case ec::InputType::key_pressed:
				case ec::InputType::key_released:
				{
					const auto& e = event.m_event.m_key;
					widget->OnKey(e.m_key, e.m_scancode, e.m_mods, e.m_pressed);
					break;
				}
				case ec::InputType::text:
				{
					const auto& e = event.m_event.m_text;
					widget->OnText(e.m_codepoint, e.m_mods);
					break;
				}
				case ec::InputType::drop:
				{
					const auto& e = event.m_event.m_drop;
					widget->OnDrop(CursorPos(e.m_window), e.m_count, e.m_paths);
					break;
				}
				case ec::InputType::resize:
				{
					const auto& e = event.m_event.m_resize;
					widget->OnResize(glm::ivec2(e.m_width, e.m_height));
					break;
				}
			}
		}
	}
}