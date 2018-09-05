#pragma once
#include "EC3D/Common/Common.h"

#include <memory>

struct GLFWwindow;

namespace ec
{
	class Window;
	class EventSource;
	class EventQueue;

	class EC3D_DECLSPEC Mouse
	{
	public:
		using EventSource_Ptr = std::unique_ptr<EventSource>;

		explicit Mouse();
		~Mouse();

		/** Install the mouse, which generates mouse events. */
		void install(Window* window);
		/** Uninstall the mouse. */
		void uninstall();

		/** Get the window, which is associated with this mouse. */
		GLFWwindow* getWindow() const;

	private:
		static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static void cursorEnterCallback(GLFWwindow* window, int entered);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		GLFWwindow* m_window = nullptr;
	};
}