#include "EC3D/Core/WindowCallbacks.h"

#include "EC3D/Core/Window.h"

namespace ec
{
	WindowCallbacks::WindowCallbacks()
	{
	}

	WindowCallbacks::~WindowCallbacks()
	{
	}

	void WindowCallbacks::initCallbacks(Window* window)
	{
		m_window = window;
		auto glfwWindow = m_window->getWindow();

		printf("Initializing Callbacks...\n");
		glfwSetWindowUserPointer(glfwWindow, window);

		// Error callback
		glfwSetErrorCallback(WindowCallbacks::errorCallback);
		setErrorCallback(
			[](int error, const char* description)
			{
				printf("ERROR: (%d) %s\n", error, description);
			});


		// Install all other devices (keyboard, mouse etc.)
		m_window->getEventSystem().getDeviceRegistry().installAll();

		// Joystick
		/// \todo Create joystick device and add entry in DeviceRegistry

		// Window callbacks
		glfwSetDropCallback(glfwWindow, WindowCallbacks::dropCallback);
		glfwSetFramebufferSizeCallback(glfwWindow, WindowCallbacks::resizeCallback);
		glfwSetWindowFocusCallback(glfwWindow, WindowCallbacks::focusCallback);
		glfwSetWindowCloseCallback(glfwWindow, WindowCallbacks::closeCallback);
		glfwSetWindowRefreshCallback(glfwWindow, WindowCallbacks::refreshCallback);
		glfwSetWindowIconifyCallback(glfwWindow, WindowCallbacks::iconifyCallback);
	}

	void WindowCallbacks::errorCallback(int error, const char* description)
	{
		s_errorCallback(error, description);
	}

	void WindowCallbacks::setErrorCallback(const ErrorCallback_T& callback)
	{
		s_errorCallback = callback;
	}

	void WindowCallbacks::dropCallback(GLFWwindow* window, const int count, const char** paths)
	{
		InputEvent inputEvent(InputType::drop);
		auto& dropEvent = inputEvent.m_event.m_drop;

		dropEvent = DropEvent(0, 0,
							  window,
							  count, paths);

		auto userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		auto& inputObserver = userWindow->getEventSystem();
		inputObserver.dispatchEvent(inputEvent);
	}

	void WindowCallbacks::resizeCallback(GLFWwindow* window, const int width, const int height)
	{
		auto userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		userWindow->resizeWindow(window, width, height);

		InputEvent inputEvent(InputType::resize);
		auto& displayEvent = inputEvent.m_event.m_display;

		displayEvent = DisplayEvent(window, 0, 0, width, height);

		auto& inputObserver = userWindow->getEventSystem();
		inputObserver.dispatchEvent(inputEvent);
	}

	void WindowCallbacks::positionCallback(GLFWwindow* window, int positionX, int positionY)
	{
		InputEvent inputEvent(InputType::window_move);
		auto& displayEvent = inputEvent.m_event.m_display;

		displayEvent = DisplayEvent(window, positionX, positionY, 0, 0);

		auto userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		auto& inputObserver = userWindow->getEventSystem();
		inputObserver.dispatchEvent(inputEvent);
	}

	void WindowCallbacks::focusCallback(GLFWwindow* window, const int focused)
	{
		InputEvent inputEvent;
		auto& displayEvent = inputEvent.m_event.m_display;

		displayEvent = DisplayEvent(window, 0, 0, 0, 0);

		auto userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		auto& inputObserver = userWindow->getEventSystem();
		if(focused == GLFW_TRUE)
		{
			inputEvent.m_type = InputType::gained_focus;
		}
		else if(focused == GLFW_FALSE)
		{
			inputEvent.m_type = InputType::lost_focus;
		}
		inputObserver.dispatchEvent(inputEvent);
	}

	void WindowCallbacks::closeCallback(GLFWwindow* window)
	{
		InputEvent inputEvent(InputType::closed);
		auto& displayEvent = inputEvent.m_event.m_display;

		displayEvent = DisplayEvent(window, 0, 0, 0, 0);

		auto userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		auto& inputObserver = userWindow->getEventSystem();
		inputObserver.dispatchEvent(inputEvent);
	}

	void WindowCallbacks::refreshCallback(GLFWwindow* window)
	{
		auto* userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

		/// \todo: render from here.
	}

	void WindowCallbacks::iconifyCallback(GLFWwindow* window, const int iconified)
	{
		InputEvent inputEvent;
		auto& displayEvent = inputEvent.m_event.m_display;

		displayEvent = DisplayEvent(window, 0, 0, 0, 0);

		inputEvent.m_type = iconified == GLFW_TRUE ? InputType::minimized : InputType::restored;

		auto userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		auto& inputObserver = userWindow->getEventSystem();
		inputObserver.dispatchEvent(inputEvent);
	}

	ec::WindowCallbacks::ErrorCallback_T WindowCallbacks::s_errorCallback = nullptr;
}