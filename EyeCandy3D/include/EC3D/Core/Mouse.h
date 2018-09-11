#pragma once
#include "EC3D/Common/Common.h"

#include <glm/glm.hpp>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

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
		enum EC3D_DECLSPEC EC_KEY_MOUSE : int
		{
			MOUSE_1 = GLFW_MOUSE_BUTTON_1,
			MOUSE_2 = GLFW_MOUSE_BUTTON_2,
			MOUSE_3 = GLFW_MOUSE_BUTTON_3,
			MOUSE_4 = GLFW_MOUSE_BUTTON_4,
			MOUSE_5 = GLFW_MOUSE_BUTTON_5,
			MOUSE_6 = GLFW_MOUSE_BUTTON_6,
			MOUSE_7 = GLFW_MOUSE_BUTTON_7,
			MOUSE_8 = GLFW_MOUSE_BUTTON_8,

			MOUSE_LAST = GLFW_MOUSE_BUTTON_LAST,
			MOUSE_LEFT = GLFW_MOUSE_BUTTON_LEFT,
			MOUSE_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
			MOUSE_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
		};
		static const char* mouseKeyToString(EC_KEY_MOUSE mouseCode);
		static bool keycodeIsMouse(int keycode);

		using EventSource_Ptr = std::unique_ptr<EventSource>;

		explicit Mouse();
		~Mouse();

		/** Install the mouse, which generates mouse events. */
		void install(Window* window);
		/** Uninstall the mouse. */
		void uninstall();

		/** Get the window, which is associated with this mouse. */
		GLFWwindow* getWindow() const;

		/** Get the current position of the cursor in window coordinates. */
		glm::ivec2 getCursorPos() const;

		/** Check if a mouse button is being pressed. */
		bool isKeyDown(Mouse::EC_KEY_MOUSE key) const;
		/** Check if a mouse button is being released. */
		bool isKeyUp(Mouse::EC_KEY_MOUSE key) const;

	private:
		static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static void cursorEnterCallback(GLFWwindow* window, int entered);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		GLFWwindow* m_window = nullptr;
	};
}