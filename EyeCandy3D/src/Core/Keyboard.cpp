#include "EC3D/Core/Keyboard.h"
#include "EC3D/Core/EventSource.h"
#include "EC3D/Core/EventQueue.h"
#include "EC3D/Core/InputEvent.h"
#include "EC3D/Core/Window.h"

#include <GLFW/glfw3.h>

namespace ec
{
	Keyboard::Keyboard()
		: m_eventSource{nullptr},
		m_window{nullptr},
		m_eventQueue{nullptr}
	{
	}

	Keyboard::~Keyboard()
	{
	}

	void Keyboard::Install(Window* window)
	{
		if(m_eventSource)
		{
			Uninstall();
		}
		m_eventSource = std::make_unique<EventSource>();
		m_window = window->GetWindow();
		m_eventQueue = window->GetEventQueue();

		glfwSetKeyCallback(m_window, Keyboard::KeyCallback);
		glfwSetCharModsCallback(m_window, Keyboard::CharModsCallback);
	}

	void Keyboard::Uninstall()
	{
		m_eventSource = nullptr;
		m_window = nullptr;
		m_eventQueue = nullptr;

		glfwSetKeyCallback(nullptr, Keyboard::KeyCallback);
		glfwSetCharModsCallback(nullptr, Keyboard::CharModsCallback);
	}

	ec::EventSource* Keyboard::GetEventSource()
	{
		return m_eventSource.get();
	}

	GLFWwindow* Keyboard::GetWindow()
	{
		return m_window;
	}

	void Keyboard::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		InputEvent inputEvent;
		auto& keyboardEvent = inputEvent.m_event.m_keyboard;

		keyboardEvent = KeyboardEvent(window, key, scancode, 0, mods, false);

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver();
		if(action == GLFW_PRESS)
		{
			inputEvent.m_type = InputType::key_pressed;
		}
		else if(action == GLFW_RELEASE)
		{
			inputEvent.m_type = InputType::key_released;
		}
		inputObserver.ReceiveEvent(inputEvent);
	}

	void Keyboard::CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
	{
		InputEvent inputEvent(InputType::text);
		auto& keyboardEvent = inputEvent.m_event.m_keyboard;

		keyboardEvent = KeyboardEvent(window, 0, 0, codepoint, mods, false);

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver();
		inputObserver.ReceiveEvent(inputEvent);
	}
}