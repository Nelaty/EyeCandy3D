#include "EC3D/Core/Mouse.h"
#include "EC3D/Core/EventSource.h"
#include "EC3D/Core/EventQueue.h"
#include "EC3D/Core/InputEvent.h"
#include "EC3D/Core/Window.h"

#include <GLFW/glfw3.h>

namespace ec
{
	Mouse::Mouse()
		: m_eventSource{nullptr},
		m_window{nullptr},
		m_eventQueue{nullptr}
	{
	}

	Mouse::~Mouse()
	{
	}

	void Mouse::Install(Window* window)
	{
		if(m_eventSource)
		{
			Uninstall();
		}
		m_eventSource = std::make_unique<EventSource>();
		m_window = window->GetWindow();
		m_eventQueue = window->GetEventQueue();

		glfwSetCursorPosCallback(m_window, Mouse::CursorPosCallback);
		glfwSetCursorEnterCallback(m_window, Mouse::CursorEnterCallback);
		glfwSetMouseButtonCallback(m_window, Mouse::MouseButtonCallback);
		glfwSetScrollCallback(m_window, Mouse::ScrollCallback);
	}

	void Mouse::Uninstall()
	{
		m_eventSource = nullptr;
		m_window = nullptr;
		m_eventQueue = nullptr;

		glfwSetCursorPosCallback(nullptr, Mouse::CursorPosCallback);
		glfwSetCursorEnterCallback(nullptr, Mouse::CursorEnterCallback);
		glfwSetMouseButtonCallback(nullptr, Mouse::MouseButtonCallback);
		glfwSetScrollCallback(nullptr, Mouse::ScrollCallback);
	}

	ec::EventSource* Mouse::GetEventSource()
	{
		return m_eventSource.get();
	}

	GLFWwindow* Mouse::GetWindow()
	{
		return m_window;
	}

	void Mouse::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
	{
		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver();

		InputEvent inputEvent(InputType::mouse_move);
		auto& mouseEvent = inputEvent.m_event.m_mouse;

		mouseEvent = MouseEvent(window,
								static_cast<int>(xpos), static_cast<int>(ypos), 0, 0,
								0, 0, 0, 0,
								0, 0);

		inputObserver.ReceiveEvent(inputEvent);
	}

	void Mouse::CursorEnterCallback(GLFWwindow* window, int entered)
	{
		InputEvent inputEvent;
		auto& mouseEvent = inputEvent.m_event.m_mouse;

		mouseEvent = MouseEvent(window,
								0, 0, 0, 0,
								0, 0, 0, 0,
								0, 0);

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver();
		if(entered == GLFW_TRUE)
		{
			inputEvent.m_type = InputType::mouse_enter;
		}
		else
		{
			inputEvent.m_type = InputType::mouse_left;
		}
		inputObserver.ReceiveEvent(inputEvent);
	}

	void Mouse::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		InputEvent inputEvent;
		auto& mouseEvent = inputEvent.m_event.m_mouse;

		mouseEvent = MouseEvent(window,
								0, 0, 0, 0,
								0, 0, 0, 0,
								button, mods);

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver();
		if(action == GLFW_PRESS)
		{
			inputEvent.m_type = InputType::mouse_button_pressed;
			mouseEvent.m_pressure = 1.0f;
		}
		else if(action == GLFW_RELEASE)
		{
			inputEvent.m_type = InputType::mouse_button_released;
			mouseEvent.m_pressure = 0.0f;
		}
		inputObserver.ReceiveEvent(inputEvent);
	}

	void Mouse::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		InputEvent inputEvent(InputType::mouse_scroll);
		auto& mouseEvent = inputEvent.m_event.m_mouse;

		mouseEvent = MouseEvent(window,
								0, 0, 0, 0,
								0, 0, static_cast<int>(xoffset), static_cast<int>(yoffset),
								0, 0);

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver();
		inputObserver.ReceiveEvent(inputEvent);
	}
}