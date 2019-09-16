#pragma once
#include <functional>

struct GLFWwindow;

namespace ec
{
	class Window;

	class WindowCallbacks
	{
	public:
		using ErrorCallback_T = std::function<void(int error, const char* description)>;

		explicit WindowCallbacks();
		~WindowCallbacks();

		void initCallbacks(Window* window);

		/** Error callback */
		static void errorCallback(int error, const char* description);
		static void setErrorCallback(const ErrorCallback_T& callback);

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

	private:
		Window* m_window;
	
		static ErrorCallback_T s_errorCallback;
	};
}