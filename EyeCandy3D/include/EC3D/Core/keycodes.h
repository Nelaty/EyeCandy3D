#pragma once
#include "EC3D/Common/Common.h"

#include <GLFW/glfw3.h>

#include <map>

namespace ec
{
	namespace key
	{
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
			DELETE = GLFW_KEY_DELETE,
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

			KEY_LAST = GLFW_KEY_LAST
		};

		static const std::map<EC_KEY_KEYBOARD, const char*> g_keyboard_key_string_lookup =
		{
			{A, "a"},
			{B, "b"},
			{C, "c"},
			{D, "d"},
			{E, "e"},
			{F, "f"},
			{G, "g"},
			{H, "h"},
			{I, "i"},
			{J, "j"},
			{K, "k"},
			{L, "l"},
			{M, "m"},
			{N, "n"},
			{O, "o"},
			{P, "p"},
			{Q, "q"},
			{R, "r"},
			{S, "s"},
			{T, "t"},
			{U, "u"},
			{V, "v"},
			{W, "w"},
			{X, "x"},
			{Y, "y"},
			{Z, "z"},

			// 0 - 9
			{KEY_0, "KEY_0"},
			{KEY_1, "KEY_1"},
			{KEY_2, "KEY_2"},
			{KEY_3, "KEY_3"},
			{KEY_4, "KEY_4"},
			{KEY_5, "KEY_5"},
			{KEY_6, "KEY_6"},
			{KEY_7, "KEY_7"},
			{KEY_8, "KEY_8"},
			{KEY_9, "KEY_9"},

			// Num pad
			{NUM_PAD_0, "num_pad_0"},
			{NUM_PAD_1, "num_pad_1"},
			{NUM_PAD_2, "num_pad_2"},
			{NUM_PAD_3, "num_pad_3"},
			{NUM_PAD_4, "num_pad_4"},
			{NUM_PAD_5, "num_pad_5"},
			{NUM_PAD_6, "num_pad_6"},
			{NUM_PAD_7, "num_pad_7"},
			{NUM_PAD_8, "num_pad_8"},
			{NUM_PAD_9, "num_pad_9"},

			{NUM_PAD_ENTER, "num_pad_enter"},
			{NUM_PAD_DECIMAL, "num_pad_decimal"},
			{NUM_PAD_DIVIDE, "num_pad_divide"},
			{NUM_PAD_MULTIPLY, "num_pad_multiply"},
			{NUM_PAD_SUBTRACT, "num_pad_subtract"},
			{NUM_PAD_ADD, "num_pad_add"},
			{NUM_PAD_ENTER, "num_pad_enter"},
			{NUM_PAD_EQUAL, "num_pad_equal"},

			// F1 - F12
			{F1, "f1"},
			{F2, "f2"},
			{F3, "f3"},
			{F4, "f4"},
			{F5, "f5"},
			{F6, "f6"},
			{F7, "f7"},
			{F8, "f8"},
			{F9, "f9"},
			{F10, "f10"},
			{F11, "f11"},
			{F12, "f12"},
			{F13, "f13"},
			{F14, "f14"},
			{F15, "f15"},
			{F16, "f16"},
			{F17, "f17"},
			{F18, "f18"},
			{F19, "f19"},
			{F20, "f20"},
			{F21, "f21"},
			{F22, "f22"},
			{F23, "f23"},
			{F24, "f24"},
			{F25, "f25"},

			// Arrow keys
			{RIGHT, "right"},
			{LEFT, "left"},
			{DOWN, "down"},
			{UP, "up"},


			{KEY_UNKNOWN, "key_unkown"},
			{SPACE, "space"},
			{APOSTROPHE, "apostrophe"},
			{COMMA, "comma"},
			{MINUS, "minus"},
			{PERIOD, "period"},
			{SLASH, "slash"},
			{SEMICOLON, "semicolon"},
			{EQUAL, "equal"},
			{LEFT_BRACKET, "left_bracket"},
			{BACKSLASH, "backslash"},
			{RIGHT_BRACKET, "right_bracket"},
			{GRAVE_ACCENT, "grave_accent"},
			{WORLD_1, "world_1"},
			{WORLD_2, "world_2"},
			{ESCAPE, "escape"},
			{ENTER, "enter"},
			{TAB, "tab"},
			{BACKSPACE, "backspace"},

			{INSERT, "insert"},
			{DELETE, "delete"},
			{PAGE_UP, "page_up"},
			{PAGE_DOWN, "page_down"},
			{HOME, "home"},
			{END, "end"},

			{PRINT_SCREEN, "print_screen"},
			{PAUSE, "pause"},
			{SCROLL_LOCK, "scroll_lock"},

			{CAPS_LOCK, "caps_lock"},
			{NUM_LOCK, "num_lock"},
			{MENU, "menu"},

			{KEY_LAST, "key_last"}
		};

		enum EC3D_DECLSPEC EC_KEY_MOUSE
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

		static const std::map<EC_KEY_MOUSE, const char*> g_mouse_key_string_lookup =
		{
			{MOUSE_1, "mouse_1"},
			{MOUSE_2, "mouse_2"},
			{MOUSE_3, "mouse_3"},
			{MOUSE_4, "mouse_4"},
			{MOUSE_5, "mouse_5"},
			{MOUSE_6, "mouse_6"},
			{MOUSE_7, "mouse_7"},
			{MOUSE_8, "mouse_8"},

			{MOUSE_LEFT, "mouse_left"},
			{MOUSE_RIGHT, "mouse_right"},
			{MOUSE_MIDDLE, "mouse_middle"},

			{MOUSE_LAST, "mouse_last"}
		};

		enum EC3D_DECLSPEC EC_KEYMOD : int
		{
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
			SUPER_RIGHT = GLFW_KEY_RIGHT_SUPER
		};

		static const std::map<EC_KEYMOD, const char*> g_keymod_string_lookup =
		{
			{SHIFT, "shift"},
			{SHIFT_LEFT, "shift_left"},
			{SHIFT_RIGHT, "shift_right"},

			{CONTROL, "ctrl"},
			{CONTROL_LEFT, "ctrl_left"},
			{CONTROL_RIGHT, "ctrl_right"},

			{ALT, "alt"},
			{ALT_LEFT, "alt_left"},
			{ALT_RIGHT, "alt_right"},

			{SUPER, "super"},
			{SUPER_LEFT, "super_left"},
			{SUPER_RIGHT, "super_right"}
		};
		
		static const char* keyboardKeyToString(const EC_KEY_KEYBOARD keyboardCode)
		{
			const auto foundIt = g_keyboard_key_string_lookup.find(keyboardCode);
			if(foundIt == g_keyboard_key_string_lookup.end())
			{
				return "not_found";
			}
			return foundIt->second;
		}

		static const char* mouseKeyToString(const EC_KEY_MOUSE mouseCode)
		{
			const auto foundIt = g_mouse_key_string_lookup.find(static_cast<EC_KEY_MOUSE>(mouseCode));
			if(foundIt == g_mouse_key_string_lookup.end())
			{
				return "not_found";
			}
			return foundIt->second;
		}

		static const char* keymodToString(const EC_KEYMOD keymod)
		{
			const auto foundIt = g_keymod_string_lookup.find(static_cast<EC_KEYMOD>(keymod));
			if(foundIt == g_keymod_string_lookup.end())
			{
				return "not_found";
			}
			return foundIt->second;
		}

		static bool keycodeIsKey(int keycode)
		{
			const auto foundEntry = g_keyboard_key_string_lookup.find(static_cast<EC_KEY_KEYBOARD>(keycode));
			return foundEntry != g_keyboard_key_string_lookup.end();
		}

		static bool keycodeIsMouse(int keycode)
		{
			const auto foundEntry = g_mouse_key_string_lookup.find(static_cast<EC_KEY_MOUSE>(keycode));
			return foundEntry != g_mouse_key_string_lookup.end();
		}

		static bool KeycodeIsKeymod(int keycode)
		{
			const auto foundEntry = g_keymod_string_lookup.find(static_cast<EC_KEYMOD>(keycode));
			return foundEntry != g_keymod_string_lookup.end();
		}
	}
}