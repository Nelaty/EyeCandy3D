#pragma once
#include "EC3D/Common/Common.h"

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
	 * \brief Representation of a physical keyboard.
	 */
	class EC3D_DECLSPEC Keyboard
	{
	public:
		/**
		 * \brief Contains all possible types of keys on a keyboard.
		 */
		enum EC3D_DECLSPEC EC_KEY_KEYBOARD : int
		{
			// A - Z
			A = GLFW_KEY_A,
			B = GLFW_KEY_B,
			C = GLFW_KEY_C,
			D = GLFW_KEY_D,
			E = GLFW_KEY_E,
			F = GLFW_KEY_F,
			G = GLFW_KEY_G,
			H = GLFW_KEY_H,
			I = GLFW_KEY_I,
			J = GLFW_KEY_J,
			K = GLFW_KEY_K,
			L = GLFW_KEY_L,
			M = GLFW_KEY_M,
			N = GLFW_KEY_N,
			O = GLFW_KEY_O,
			P = GLFW_KEY_P,
			Q = GLFW_KEY_Q,
			R = GLFW_KEY_R,
			S = GLFW_KEY_S,
			T = GLFW_KEY_T,
			U = GLFW_KEY_U,
			V = GLFW_KEY_V,
			W = GLFW_KEY_W,
			X = GLFW_KEY_X,
			Y = GLFW_KEY_Y,
			Z = GLFW_KEY_Z,

			// 0 - 9
			KEY_0 = GLFW_KEY_0,
			KEY_1 = GLFW_KEY_1,
			KEY_2 = GLFW_KEY_2,
			KEY_3 = GLFW_KEY_3,
			KEY_4 = GLFW_KEY_4,
			KEY_5 = GLFW_KEY_5,
			KEY_6 = GLFW_KEY_6,
			KEY_7 = GLFW_KEY_7,
			KEY_8 = GLFW_KEY_8,
			KEY_9 = GLFW_KEY_9,

			// Num pad
			NUM_PAD_0 = GLFW_KEY_KP_0,
			NUM_PAD_1 = GLFW_KEY_KP_1,
			NUM_PAD_2 = GLFW_KEY_KP_2,
			NUM_PAD_3 = GLFW_KEY_KP_3,
			NUM_PAD_4 = GLFW_KEY_KP_4,
			NUM_PAD_5 = GLFW_KEY_KP_5,
			NUM_PAD_6 = GLFW_KEY_KP_6,
			NUM_PAD_7 = GLFW_KEY_KP_7,
			NUM_PAD_8 = GLFW_KEY_KP_8,
			NUM_PAD_9 = GLFW_KEY_KP_9,

			NUM_PAD_DECIMAL = GLFW_KEY_KP_DECIMAL,
			NUM_PAD_DIVIDE = GLFW_KEY_KP_DIVIDE,
			NUM_PAD_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
			NUM_PAD_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
			NUM_PAD_ADD = GLFW_KEY_KP_ADD,
			NUM_PAD_ENTER = GLFW_KEY_KP_ENTER,
			NUM_PAD_EQUAL = GLFW_KEY_KP_EQUAL,

			// F1 - F12
			F1 = GLFW_KEY_F1,
			F2 = GLFW_KEY_F2,
			F3 = GLFW_KEY_F3,
			F4 = GLFW_KEY_F4,
			F5 = GLFW_KEY_F5,
			F6 = GLFW_KEY_F6,
			F7 = GLFW_KEY_F7,
			F8 = GLFW_KEY_F8,
			F9 = GLFW_KEY_F9,
			F10 = GLFW_KEY_F10,
			F11 = GLFW_KEY_F11,
			F12 = GLFW_KEY_F12,
			F13 = GLFW_KEY_F13,
			F14 = GLFW_KEY_F14,
			F15 = GLFW_KEY_F15,
			F16 = GLFW_KEY_F16,
			F17 = GLFW_KEY_F17,
			F18 = GLFW_KEY_F18,
			F19 = GLFW_KEY_F19,
			F20 = GLFW_KEY_F20,
			F21 = GLFW_KEY_F21,
			F22 = GLFW_KEY_F22,
			F23 = GLFW_KEY_F23,
			F24 = GLFW_KEY_F24,
			F25 = GLFW_KEY_F25,

			// Arrow keys
			RIGHT = GLFW_KEY_RIGHT,
			LEFT = GLFW_KEY_LEFT,
			DOWN = GLFW_KEY_DOWN,
			UP = GLFW_KEY_UP,


			KEY_UNKNOWN = GLFW_KEY_UNKNOWN,
			SPACE = GLFW_KEY_SPACE,
			APOSTROPHE = GLFW_KEY_APOSTROPHE, /* ' */
			COMMA = GLFW_KEY_COMMA, /* , */
			MINUS = GLFW_KEY_MINUS, /* - */
			PERIOD = GLFW_KEY_PERIOD, /* . */
			SLASH = GLFW_KEY_SLASH, /* / */
			SEMICOLON = GLFW_KEY_SEMICOLON, /* ; */
			EQUAL = GLFW_KEY_EQUAL, /* = */
			LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET, /* [ */
			BACKSLASH = GLFW_KEY_BACKSLASH, /* \ */
			RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET, /* ] */
			GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT, /* ` */
			WORLD_1 = GLFW_KEY_WORLD_1, /* non-US #1 */
			WORLD_2 = GLFW_KEY_WORLD_2, /* non-US #2 */
			ESCAPE = GLFW_KEY_ESCAPE,
			ENTER = GLFW_KEY_ENTER,
			TAB = GLFW_KEY_TAB,
			BACKSPACE = GLFW_KEY_BACKSPACE,

			INSERT = GLFW_KEY_INSERT,
			DEL = GLFW_KEY_DELETE,
			PAGE_UP = GLFW_KEY_PAGE_UP,
			PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
			HOME = GLFW_KEY_HOME,
			END = GLFW_KEY_END,

			PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
			PAUSE = GLFW_KEY_PAUSE,
			SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,

			CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
			NUM_LOCK = GLFW_KEY_NUM_LOCK,
			MENU = GLFW_KEY_MENU,

			// Keymods
			SHIFT = GLFW_MOD_SHIFT,
			SHIFT_LEFT = GLFW_KEY_LEFT_SHIFT,
			SHIFT_RIGHT = GLFW_KEY_RIGHT_SHIFT,

			CONTROL = GLFW_MOD_CONTROL,
			CONTROL_LEFT = GLFW_KEY_LEFT_CONTROL,
			CONTROL_RIGHT = GLFW_KEY_RIGHT_CONTROL,

			ALT = GLFW_MOD_ALT,
			ALT_LEFT = GLFW_KEY_LEFT_ALT,
			ALT_RIGHT = GLFW_KEY_RIGHT_ALT,

			SUPER = GLFW_MOD_SUPER,
			SUPER_LEFT = GLFW_KEY_LEFT_SUPER,
			SUPER_RIGHT = GLFW_KEY_RIGHT_SUPER,

			KEY_LAST = GLFW_KEY_LAST
		};

		/**
		 * \brief Convert a keycode to its string representation.
		 */
		static const char* keyboardKeyToString(EC_KEY_KEYBOARD keyboardCode);
		/**
		 * \brief Check if a keycode is representing a key on the
		 * keyboard.
		 * \brief keycode 
		 */
		static bool keycodeIsKey(int keycode);

	public: 
		using EventSource_Ptr = std::unique_ptr<EventSource>;

		explicit Keyboard();
		~Keyboard();

		/**
		 * \brief Install the keyboard, which generates keyboard
		 * events. 
		 * \param window The window, for which keyboard events will
		 * now be generated.
		 */
		void install(Window* window);
		/**
		 * \brief Uninstall the keyboard. 
		 */
		void uninstall();

		/** 
		 * \brief Get the window, which is associated with this keyboard. 
		 */
		GLFWwindow* getWindow() const;

		/**
		 * \brief Check if a keyboard button is being pressed.
		 */
		bool isKeyDown(Keyboard::EC_KEY_KEYBOARD key) const;
		/** 
		 * \brief Check if a keyboard button is being released. 
		 */
		bool isKeyUp(Keyboard::EC_KEY_KEYBOARD key) const;
	
	private:
		/**
		 * \brief Key callback which can be associated with a window.
		 */
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		/**
		 * \brief Char mods callback which can be associated with a
		 * window.
		 */
		static void charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
	
		GLFWwindow* m_window = nullptr;
	};
}