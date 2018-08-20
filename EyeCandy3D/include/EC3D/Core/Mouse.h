#pragma once
#include <memory>

struct GLFWwindow;

namespace ec
{
	class Window;
	class EventSource;
	class EventQueue;

	class Mouse
	{
	public:
		using EventSource_Ptr = std::unique_ptr<EventSource>;

	public:
		explicit Mouse();
		~Mouse();

		/** Install the mouse, which generates mouse events. */
		void Install(Window* window);
		/** Uninstall the mouse. */
		void Uninstall();

		EventSource* GetEventSource();
		GLFWwindow* GetWindow();

	private:
		static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static void CursorEnterCallback(GLFWwindow* window, int entered);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		EventSource_Ptr m_eventSource;
		EventQueue* m_eventQueue;
		GLFWwindow* m_window;
	};
}