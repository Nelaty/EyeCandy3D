//
// Created by nelaty on 27.11.20.
//

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ec
{
    class Window;

    class WindowCallbacks
    {
    public:
        explicit WindowCallbacks() = default;
        ~WindowCallbacks() = default;

        void init(GLFWwindow* glfwWindow, Window* window);

    private:
        /**
		 * \brief The drop callback is called when one or multiple
		 * files are dragged into the window
		 */
        static void dropCallback(GLFWwindow* window, int count, const char** paths);
        /**
         * \brief The resize callback is called when the window's
         * width or height has changed.
         */
        static void resizeCallback(GLFWwindow* window, int width, int height);
        /**
         * \brief The position callback is called when the window's
         * position changes.
         */
        static void positionCallback(GLFWwindow* window, int positionX, int positionY);
        /**
         * \brief The focus callback is called when a window, which
         * previously was unfocused, receives focus.
         */
        static void focusCallback(GLFWwindow* window, int focused);
        /**
         * \brief The close callback is called when a window is
         * being destroyed.
         */
        static void closeCallback(GLFWwindow* window);
        /**
         * \brief The refresh callback is called when a window
         * should be redrawn.
         */
        static void refreshCallback(GLFWwindow* window);
        /**
         * \brief The iconify callback is called when a window was
         * minimized or restored.
         */
        static void iconifyCallback(GLFWwindow* window, int iconified);

        GLFWwindow* m_glfwWindow;
        Window* m_window;
    };
}
