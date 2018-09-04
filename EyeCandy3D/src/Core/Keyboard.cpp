#include "EC3D/Core/Keyboard.h"
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
		m_window = window->getWindow();

		glfwSetKeyCallback(m_window, Keyboard::keyCallback);
		glfwSetCharModsCallback(m_window, Keyboard::charModsCallback);
	}

	void Keyboard::uninstall()
	{
		m_window = nullptr;

		glfwSetKeyCallback(nullptr, Keyboard::keyCallback);
		glfwSetCharModsCallback(nullptr, Keyboard::charModsCallback);
	}

	GLFWwindow* Keyboard::getWindow() const
	{
		return m_window;
	}

	void Keyboard::keyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
	{
		InputEvent inputEvent;
		auto& keyboardEvent = inputEvent.m_event.m_keyboard;

		keyboardEvent = KeyboardEvent(window, key, scancode, 0, mods, false);
		
		if(action == GLFW_PRESS)
		{
			inputEvent.m_type = InputType::key_pressed;
		}
		else if(action == GLFW_RELEASE)
		{
			inputEvent.m_type = InputType::key_released;
		}

		auto& eventSystem = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
		eventSystem.dispatchEvent(inputEvent);
	}

	void Keyboard::charModsCallback(GLFWwindow* window, const unsigned int codepoint, const int mods)
	{
		InputEvent inputEvent(InputType::text);
		auto& keyboardEvent = inputEvent.m_event.m_keyboard;

		keyboardEvent = KeyboardEvent(window, 0, 0, codepoint, mods, false);
		
		auto& eventSystem = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
		eventSystem.dispatchEvent(inputEvent);
	}
}