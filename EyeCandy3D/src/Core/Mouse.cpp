#include "EC3D/Core/Mouse.h"
#include "EC3D/Core/InputEvent.h"
#include "EC3D/Core/Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ec
{
	namespace
	{
		static const std::map<Mouse::EC_KEY_MOUSE, const char*> mouse_key_string_lookup =
		{
			{Mouse::MOUSE_1, "mouse_1"},
			{Mouse::MOUSE_2, "mouse_2"},
			{Mouse::MOUSE_3, "mouse_3"},
			{Mouse::MOUSE_4, "mouse_4"},
			{Mouse::MOUSE_5, "mouse_5"},
			{Mouse::MOUSE_6, "mouse_6"},
			{Mouse::MOUSE_7, "mouse_7"},
			{Mouse::MOUSE_8, "mouse_8"},

			{Mouse::MOUSE_LEFT, "mouse_left"},
			{Mouse::MOUSE_RIGHT, "mouse_right"},
			{Mouse::MOUSE_MIDDLE, "mouse_middle"},

			{Mouse::MOUSE_LAST, "mouse_last"}
		};
	}

	static const char* mouseKeyToString(const Mouse::EC_KEY_MOUSE mouseCode)
	{
		const auto foundIt = mouse_key_string_lookup.find(static_cast<Mouse::EC_KEY_MOUSE>(mouseCode));
		if(foundIt == mouse_key_string_lookup.end())
		{
			return "not_found";
		}
		return foundIt->second;
	}

	static bool keycodeIsMouse(int keycode)
	{
		const auto foundEntry = mouse_key_string_lookup.find(static_cast<Mouse::EC_KEY_MOUSE>(keycode));
		return foundEntry != mouse_key_string_lookup.end();
	}

	Mouse::Mouse()
	= default;

	Mouse::~Mouse()
	= default;

	void Mouse::install(Window* window)
	{	
		m_window = window->getWindow();

		glfwSetCursorPosCallback(m_window, Mouse::cursorPosCallback);
		glfwSetCursorEnterCallback(m_window, Mouse::cursorEnterCallback);
		glfwSetMouseButtonCallback(m_window, Mouse::mouseButtonCallback);
		glfwSetScrollCallback(m_window, Mouse::scrollCallback);
	}

	void Mouse::uninstall()
	{
		m_window = nullptr;

		glfwSetCursorPosCallback(nullptr, Mouse::cursorPosCallback);
		glfwSetCursorEnterCallback(nullptr, Mouse::cursorEnterCallback);
		glfwSetMouseButtonCallback(nullptr, Mouse::mouseButtonCallback);
		glfwSetScrollCallback(nullptr, Mouse::scrollCallback);
	}

	GLFWwindow* Mouse::getWindow() const
	{
		return m_window;
	}

	glm::ivec2 Mouse::getCursorPos() const
	{
		double x, y;
		glfwGetCursorPos(m_window, &x, &y);
		return glm::ivec2(x, y);
	}

	bool Mouse::isKeyDown(const Mouse::EC_KEY_MOUSE key) const
	{
		const auto state = glfwGetMouseButton(m_window, key);
		return state == GLFW_PRESS;
	}

	bool Mouse::isKeyUp(const Mouse::EC_KEY_MOUSE key) const
	{
		const auto state = glfwGetMouseButton(m_window, key);
		return state == GLFW_RELEASE;
	}

	void Mouse::cursorPosCallback(GLFWwindow* window, 
								  const double xpos,
								  const double ypos)
	{
		

		InputEvent inputEvent(InputType::mouse_move);
		auto& mouseEvent = inputEvent.m_event.m_mouse;

		mouseEvent = MouseEvent(window,
								static_cast<int>(xpos), static_cast<int>(ypos), 0, 0,
								0, 0, 0, 0,
								0, 0);

		auto& eventSystem = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
		eventSystem.dispatchEvent(inputEvent);
	}

	void Mouse::cursorEnterCallback(GLFWwindow* window, const int entered)
	{
		InputEvent inputEvent;
		auto& mouseEvent = inputEvent.m_event.m_mouse;

		mouseEvent = MouseEvent(window,
								0, 0, 0, 0,
								0, 0, 0, 0,
								0, 0);

		if(entered == GLFW_TRUE)
		{
			inputEvent.m_type = InputType::mouse_enter;
		}
		else
		{
			inputEvent.m_type = InputType::mouse_left;
		}

		auto& eventSystem = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
		eventSystem.dispatchEvent(inputEvent);
	}

	void Mouse::mouseButtonCallback(GLFWwindow* window, 
									const int button, 
									const int action,
									const int mods)
	{
		InputEvent inputEvent;
		auto& mouseEvent = inputEvent.m_event.m_mouse;

		mouseEvent = MouseEvent(window,
								0, 0, 0, 0,
								0, 0, 0, 0,
								button, mods);

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

		auto& eventSystem = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
		eventSystem.dispatchEvent(inputEvent);
	}

	void Mouse::scrollCallback(GLFWwindow* window, 
							   const double xoffset,
							   const double yoffset)
	{
		InputEvent inputEvent(InputType::mouse_scroll);
		auto& mouseEvent = inputEvent.m_event.m_mouse;

		mouseEvent = MouseEvent(window,
								0, 0, 0, 0,
								0, 0, static_cast<int>(xoffset), static_cast<int>(yoffset),
								0, 0);

		auto& eventSystem = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
		eventSystem.dispatchEvent(inputEvent);
	}
}