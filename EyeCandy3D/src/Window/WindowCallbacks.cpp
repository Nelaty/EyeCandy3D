#include "EC3D/Window/WindowCallbacks.h"
#include "EC3D/Window/Window.h"
#include "EC3D/Common/Logging.h"

namespace ec {
    void WindowCallbacks::init(GLFWwindow* glfwWindow, Window* window)
    {
        m_glfwWindow = glfwWindow;
        m_window = window;

        Logger::info("(...) callback initialization");
        glfwSetWindowUserPointer(m_glfwWindow, m_window);

        // Error callback
        glfwSetErrorCallback(Window::errorCallback);

        // Install all other devices (keyboard, mouse etc.)
        m_window->getEventSystem().getDeviceRegistry().installAll();

        // Joystick
        /// \todo Create joystick device and add entry in DeviceRegistry

        // Window callbacks
        glfwSetDropCallback(m_glfwWindow, WindowCallbacks::dropCallback);
        glfwSetFramebufferSizeCallback(m_glfwWindow, WindowCallbacks::resizeCallback);
        glfwSetWindowFocusCallback(m_glfwWindow, WindowCallbacks::focusCallback);
        glfwSetWindowCloseCallback(m_glfwWindow, WindowCallbacks::closeCallback);
        glfwSetWindowRefreshCallback(m_glfwWindow, WindowCallbacks::refreshCallback);
        glfwSetWindowIconifyCallback(m_glfwWindow, WindowCallbacks::iconifyCallback);
    }

    void WindowCallbacks::dropCallback(GLFWwindow* window, const int count, const char** paths)
    {
        InputEvent inputEvent(InputType::drop);
        auto& dropEvent = inputEvent.m_event.m_drop;

        dropEvent = DropEvent(0, 0,
                              window,
                              count, paths);

        auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
        inputObserver.dispatchEvent(inputEvent);
    }

    void WindowCallbacks::resizeCallback(GLFWwindow* window, const int width, const int height)
    {
        auto* userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
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

        auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
        inputObserver.dispatchEvent(inputEvent);
    }

    void WindowCallbacks::focusCallback(GLFWwindow* window, const int focused)
    {
        InputEvent inputEvent;
        auto& displayEvent = inputEvent.m_event.m_display;

        displayEvent = DisplayEvent(window, 0, 0, 0, 0);

        auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
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

        auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
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

        auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
        inputObserver.dispatchEvent(inputEvent);
    }
}