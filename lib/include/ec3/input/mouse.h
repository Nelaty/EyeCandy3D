#pragma once
#include "ec3/common/common.h"

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

	/**
	 * \brief Represents a physical mouse.
	 */
	class EC3D_DECLSPEC Mouse
	{
	public:
		/**
		 * \brief Collection of all mouse buttons
		 */
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

			MOUSE_LEFT = GLFW_MOUSE_BUTTON_LEFT,
			MOUSE_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
			MOUSE_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
			MOUSE_LAST = GLFW_MOUSE_BUTTON_LAST
		};

		/**
		 * \brief Convert a mouse button code to its string
		 * representation.
		 */
		static const char* mouseKeyToString(EC_KEY_MOUSE mouseCode);
		/**
		 * \brief Check if a keycode is representing a mouse button.
		 */
		static bool keycodeIsMouse(int keycode);

	public:
		using EventSource_Ptr = std::unique_ptr<EventSource>;

		explicit Mouse();
		~Mouse();

		/**
		 * \brief Install the mouse, which generates mouse events.
		 * \param window The window, which should create mouse events.
		 */
		void install(Window* window);
		/** 
		 * \brief Uninstall the mouse.
		 */
		void uninstall();

		/** 
		 * \brief Get the window, which is associated with this mouse.
		 */
		GLFWwindow* getWindow() const;

		/** 
		 * \brief Get the current position of the cursor in window 
		 * coordinates. 
		 */
		glm::ivec2 getCursorPos() const;

		/**
		 * \brief Check if a mouse button is being pressed. 
		 */
		bool isKeyDown(Mouse::EC_KEY_MOUSE key) const;
		/** 
		 * \brief Check if a mouse button is being released. 
		 */
		bool isKeyUp(Mouse::EC_KEY_MOUSE key) const;

	private:
		/**
		 * \brief Will be called, when the cursor position changes
		 * inside a window.
		 */
		static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		/**
		 * \brief Will be called, when the cursor enters or leaves
		 * a window.
		 */
		static void cursorEnterCallback(GLFWwindow* window, int entered);
		/**
		 * \brief Will be called, when a mouse button was pressed
		 * inside a window.
		 */
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		/**
		 * \brief Will be called, when the scroll wheel was used
		 * inside a window.
		 */
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		GLFWwindow* m_window = nullptr;
	};
}