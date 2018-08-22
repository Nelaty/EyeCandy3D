#include "EC3D/Core/Keyboard.h"
#include "EC3D/Core/EventSource.h"
#include "EC3D/Core/EventQueue.h"
#include "EC3D/Core/InputEvent.h"
#include "EC3D/Core/Window.h"

#include <GLFW/glfw3.h>

namespace ec
{
	Keyboard::Keyboard()
	= default;

	Keyboard::~Keyboard()
	= default;

	void Keyboard::install(Window* window)
	{
		if(m_eventSource)
		{
			uninstall();
		}
		m_eventSource = std::make_unique<EventSource>();
		m_window = window->getWindow();
		m_eventQueue = window->getEventQueue();

		glfwSetKeyCallback(m_window, Keyboard::keyCallback);
		glfwSetCharModsCallback(m_window, Keyboard::charModsCallback);
	}

	void Keyboard::uninstall()
	{
		m_eventSource = nullptr;
		m_window = nullptr;
		m_eventQueue = nullptr;

		glfwSetKeyCallback(nullptr, Keyboard::keyCallback);
		glfwSetCharModsCallback(nullptr, Keyboard::charModsCallback);
	}

	ec::EventSource* Keyboard::getEventSource() const
	{
		return m_eventSource.get();
	}

	GLFWwindow* Keyboard::getWindow() const
	{
		return m_window;
	}

	void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		InputEvent inputEvent;
		auto& keyboardEvent = inputEvent.m_event.m_keyboard;

		keyboardEvent = KeyboardEvent(window, key, scancode, 0, mods, false);

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getInputObserver();
		if(action == GLFW_PRESS)
		{
			inputEvent.m_type = InputType::key_pressed;
		}
		else if(action == GLFW_RELEASE)
		{
			inputEvent.m_type = InputType::key_released;
		}
		inputObserver.receiveEvent(inputEvent);
	}

	void Keyboard::charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
	{
		InputEvent inputEvent(InputType::text);
		auto& keyboardEvent = inputEvent.m_event.m_keyboard;

		keyboardEvent = KeyboardEvent(window, 0, 0, codepoint, mods, false);

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getInputObserver();
		inputObserver.receiveEvent(inputEvent);
	}
}