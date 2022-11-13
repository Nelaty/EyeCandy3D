#include "ec3/input/keyboard.h"

#include "ec3/input/input-event.h"
#include "ec3/window/window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>

namespace ec
{
	namespace
	{
		const std::map<Keyboard::EC_KEY_KEYBOARD, const char*> keyboard_key_string_lookup =
		{
			{Keyboard::A, "a"},
			{Keyboard::B, "b"},
			{Keyboard::C, "c"},
			{Keyboard::D, "d"},
			{Keyboard::E, "e"},
			{Keyboard::F, "f"},
			{Keyboard::G, "g"},
			{Keyboard::H, "h"},
			{Keyboard::I, "i"},
			{Keyboard::J, "j"},
			{Keyboard::K, "k"},
			{Keyboard::L, "l"},
			{Keyboard::M, "m"},
			{Keyboard::N, "n"},
			{Keyboard::O, "o"},
			{Keyboard::P, "p"},
			{Keyboard::Q, "q"},
			{Keyboard::R, "r"},
			{Keyboard::S, "s"},
			{Keyboard::T, "t"},
			{Keyboard::U, "u"},
			{Keyboard::V, "v"},
			{Keyboard::W, "w"},
			{Keyboard::X, "x"},
			{Keyboard::Y, "y"},
			{Keyboard::Z, "z"},

			// 0 - 9
			{Keyboard::KEY_0, "KEY_0"},
			{Keyboard::KEY_1, "KEY_1"},
			{Keyboard::KEY_2, "KEY_2"},
			{Keyboard::KEY_3, "KEY_3"},
			{Keyboard::KEY_4, "KEY_4"},
			{Keyboard::KEY_5, "KEY_5"},
			{Keyboard::KEY_6, "KEY_6"},
			{Keyboard::KEY_7, "KEY_7"},
			{Keyboard::KEY_8, "KEY_8"},
			{Keyboard::KEY_9, "KEY_9"},

			// Num pad
			{Keyboard::NUM_PAD_0, "num_pad_0"},
			{Keyboard::NUM_PAD_1, "num_pad_1"},
			{Keyboard::NUM_PAD_2, "num_pad_2"},
			{Keyboard::NUM_PAD_3, "num_pad_3"},
			{Keyboard::NUM_PAD_4, "num_pad_4"},
			{Keyboard::NUM_PAD_5, "num_pad_5"},
			{Keyboard::NUM_PAD_6, "num_pad_6"},
			{Keyboard::NUM_PAD_7, "num_pad_7"},
			{Keyboard::NUM_PAD_8, "num_pad_8"},
			{Keyboard::NUM_PAD_9, "num_pad_9"},

			{Keyboard::NUM_PAD_ENTER, "num_pad_enter"},
			{Keyboard::NUM_PAD_DECIMAL, "num_pad_decimal"},
			{Keyboard::NUM_PAD_DIVIDE, "num_pad_divide"},
			{Keyboard::NUM_PAD_MULTIPLY, "num_pad_multiply"},
			{Keyboard::NUM_PAD_SUBTRACT, "num_pad_subtract"},
			{Keyboard::NUM_PAD_ADD, "num_pad_add"},
			{Keyboard::NUM_PAD_ENTER, "num_pad_enter"},
			{Keyboard::NUM_PAD_EQUAL, "num_pad_equal"},

			// F1 - F12
			{Keyboard::F1, "f1"},
			{Keyboard::F2, "f2"},
			{Keyboard::F3, "f3"},
			{Keyboard::F4, "f4"},
			{Keyboard::F5, "f5"},
			{Keyboard::F6, "f6"},
			{Keyboard::F7, "f7"},
			{Keyboard::F8, "f8"},
			{Keyboard::F9, "f9"},
			{Keyboard::F10, "f10"},
			{Keyboard::F11, "f11"},
			{Keyboard::F12, "f12"},
			{Keyboard::F13, "f13"},
			{Keyboard::F14, "f14"},
			{Keyboard::F15, "f15"},
			{Keyboard::F16, "f16"},
			{Keyboard::F17, "f17"},
			{Keyboard::F18, "f18"},
			{Keyboard::F19, "f19"},
			{Keyboard::F20, "f20"},
			{Keyboard::F21, "f21"},
			{Keyboard::F22, "f22"},
			{Keyboard::F23, "f23"},
			{Keyboard::F24, "f24"},
			{Keyboard::F25, "f25"},

			// Arrow keys
			{Keyboard::RIGHT, "right"},
			{Keyboard::LEFT, "left"},
			{Keyboard::DOWN, "down"},
			{Keyboard::UP, "up"},


			{Keyboard::KEY_UNKNOWN, "key_unkown"},
			{Keyboard::SPACE, "space"},
			{Keyboard::APOSTROPHE, "apostrophe"},
			{Keyboard::COMMA, "comma"},
			{Keyboard::MINUS, "minus"},
			{Keyboard::PERIOD, "period"},
			{Keyboard::SLASH, "slash"},
			{Keyboard::SEMICOLON, "semicolon"},
			{Keyboard::EQUAL, "equal"},
			{Keyboard::LEFT_BRACKET, "left_bracket"},
			{Keyboard::BACKSLASH, "backslash"},
			{Keyboard::RIGHT_BRACKET, "right_bracket"},
			{Keyboard::GRAVE_ACCENT, "grave_accent"},
			{Keyboard::WORLD_1, "world_1"},
			{Keyboard::WORLD_2, "world_2"},
			{Keyboard::ESCAPE, "escape"},
			{Keyboard::ENTER, "enter"},
			{Keyboard::TAB, "tab"},
			{Keyboard::BACKSPACE, "backspace"},

			{Keyboard::INSERT, "insert"},
			{Keyboard::DELETE, "delete"},
			{Keyboard::PAGE_UP, "page_up"},
			{Keyboard::PAGE_DOWN, "page_down"},
			{Keyboard::HOME, "home"},
			{Keyboard::END, "end"},

			{Keyboard::PRINT_SCREEN, "print_screen"},
			{Keyboard::PAUSE, "pause"},
			{Keyboard::SCROLL_LOCK, "scroll_lock"},

			{Keyboard::CAPS_LOCK, "caps_lock"},
			{Keyboard::NUM_LOCK, "num_lock"},
			{Keyboard::MENU, "menu"},

			// Keymods
			{Keyboard::SHIFT, "shift"},
			{Keyboard::SHIFT_LEFT, "shift_left"},
			{Keyboard::SHIFT_RIGHT, "shift_right"},

			{Keyboard::CONTROL, "ctrl"},
			{Keyboard::CONTROL_LEFT, "ctrl_left"},
			{Keyboard::CONTROL_RIGHT, "ctrl_right"},

			{Keyboard::ALT, "alt"},
			{Keyboard::ALT_LEFT, "alt_left"},
			{Keyboard::ALT_RIGHT, "alt_right"},

			{Keyboard::SUPER, "super"},
			{Keyboard::SUPER_LEFT, "super_left"},
			{Keyboard::SUPER_RIGHT, "super_right"},

			{Keyboard::KEY_LAST, "key_last"}
		};
	}

	const char* Keyboard::keyboardKeyToString(const Keyboard::EC_KEY_KEYBOARD keyboardCode)
	{
		const auto foundIt = keyboard_key_string_lookup.find(keyboardCode);
		if(foundIt == keyboard_key_string_lookup.end())
		{
			return "not_found";
		}
		return foundIt->second;
	}

	bool Keyboard::keycodeIsKey(int keycode)
	{
		const auto foundEntry = keyboard_key_string_lookup.find(static_cast<Keyboard::EC_KEY_KEYBOARD>(keycode));
		return foundEntry != keyboard_key_string_lookup.end();
	}

	Keyboard::Keyboard()
	= default;

	Keyboard::~Keyboard()
	= default;

	void Keyboard::install(Window* window)
	{
		m_window = window->getWindow();

		glfwSetKeyCallback(m_window, Keyboard::keyCallback);
		glfwSetCharModsCallback(m_window, Keyboard::charModsCallback);
	}

	void Keyboard::uninstall()
	{
		m_window = nullptr;

		glfwSetKeyCallback(nullptr, Keyboard::keyCallback);
		glfwSetCharModsCallback(nullptr, Keyboard::charModsCallback);
	}

	GLFWwindow* Keyboard::getWindow() const
	{
		return m_window;
	}

	bool Keyboard::isKeyDown(const Keyboard::EC_KEY_KEYBOARD key) const
	{
		const auto state = glfwGetKey(m_window, key);
		return state == GLFW_PRESS;
	}

	bool Keyboard::isKeyUp(const Keyboard::EC_KEY_KEYBOARD key) const
	{
		const auto state = glfwGetKey(m_window, key);
		return state == GLFW_RELEASE;
	}

	void Keyboard::keyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
	{
		InputEvent inputEvent;
		auto& keyboardEvent = inputEvent.m_event.m_keyboard;

		keyboardEvent = KeyboardEvent(window, key, scancode, 0, mods, false);
		
		if(action == GLFW_PRESS)
		{
			inputEvent.m_type = InputType::key_pressed;
		}
		else if(action == GLFW_RELEASE)
		{
			inputEvent.m_type = InputType::key_released;
		}
		else // GLFW_REPEAT
		{
			return;
		}

		auto& eventSystem = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
		eventSystem.dispatchEvent(inputEvent);
	}

	void Keyboard::charModsCallback(GLFWwindow* window, const unsigned int codepoint, const int mods)
	{
		InputEvent inputEvent(InputType::text);
		auto& keyboardEvent = inputEvent.m_event.m_keyboard;

		keyboardEvent = KeyboardEvent(window, 0, 0, codepoint, mods, false);
		
		auto& eventSystem = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
		eventSystem.dispatchEvent(inputEvent);
	}
}