#include "EC3D/Core/InputEvent.h"
#include <GLFW/glfw3.h>

#include <stdio.h>

#define __NGL_SHIFT_PRESSED__(mods) ((GLFW_MOD_SHIFT & (mods)) != 0)
#define __NGL_CONTROL_PRESSED__(mods) ((GLFW_MOD_CONTROL & (mods)) != 0)
#define __NGL_ALT_PRESSED__(mods) ((GLFW_MOD_ALT & (mods)) != 0)
#define __NGL_SUPER_PRESSED__(mods) ((GLFW_MOD_SUPER & (mods)) != 0)

namespace ec
{
	// Mouse move
	MouseMoveEvent::MouseMoveEvent(GLFWwindow* window, const float x, const float y)
		: m_window{window},
		m_x{x},
		m_y{y}
	{
	}

	MouseMoveEvent::~MouseMoveEvent()
	{
	}

	void MouseMoveEvent::Print() const
	{
		printf("Mouse move event: x:%f, y:%f\n", m_x, m_y);
	}

	// Mouse drag
	MouseDragEvent::MouseDragEvent(GLFWwindow* window, const float offsetX, const float offsetY, const float x, const float y, const int button, const int modifier)
		: m_window{window},
		m_x{x},
		m_y{y},
		m_offsetX{offsetX},
		m_offsetY{offsetY},
		m_button{button},
		m_modifier{modifier}
	{
	}

	MouseDragEvent::~MouseDragEvent()
	{
	}

	void MouseDragEvent::Print() const
	{
		printf("Mouse drag event: x:%f, y:%f, x-rel:%f, y-rel:%f, button:%d, mods:%d", m_x, m_y, m_offsetX, m_offsetY, m_button, m_modifier);
	}

	bool MouseDragEvent::ShiftPressed() const
	{
		return __NGL_SHIFT_PRESSED__(m_modifier);
	}

	bool MouseDragEvent::ControlPressed() const
	{
		return __NGL_CONTROL_PRESSED__(m_modifier);
	}

	bool MouseDragEvent::AltPressed() const
	{
		return __NGL_ALT_PRESSED__(m_modifier);
	}

	bool MouseDragEvent::SuperPressed() const
	{
		return __NGL_SUPER_PRESSED__(m_modifier);
	}

	// Mouse scroll
	MouseScrollEvent::MouseScrollEvent(GLFWwindow* window, const float offsetX, const float offsetY)
		: m_window{window},
		m_offsetX{offsetX},
		m_offsetY{offsetY}
	{
	}

	MouseScrollEvent::~MouseScrollEvent()
	{
	}

	void MouseScrollEvent::Print() const
	{
		printf("Mouse scroll event: x-offset:%f, y-offset:%f\n", m_offsetX, m_offsetY);
	}

	// Mouse enter
	MouseEnterEvent::MouseEnterEvent(GLFWwindow* window, const bool entered)
		: m_window{window},
		m_entered{entered}
	{
	}

	MouseEnterEvent::~MouseEnterEvent()
	{
	}

	void MouseEnterEvent::Print() const
	{
		printf("Mouse enter event: entered %d\n", m_entered);
	}

	// Mouse button
	MouseButtonEvent::MouseButtonEvent(GLFWwindow* window, const int button, const int mods, const bool pressed)
		: m_window{window},
		m_button{button},
		m_mods{mods},
		m_pressed{pressed}
	{
	}

	MouseButtonEvent::~MouseButtonEvent()
	{
	}

	void MouseButtonEvent::Print() const
	{
		printf("Mouse button event: button:%d, mods:%d, release/press:%d\n", m_button, m_mods, m_pressed);
	}

	bool MouseButtonEvent::ShiftPressed() const
	{
		return __NGL_SHIFT_PRESSED__(m_mods);
	}

	bool MouseButtonEvent::ControlPressed() const
	{
		return __NGL_CONTROL_PRESSED__(m_mods);
	}

	bool MouseButtonEvent::AltPressed() const
	{
		return __NGL_ALT_PRESSED__(m_mods);
	}

	bool MouseButtonEvent::SuperPressed() const
	{
		return __NGL_SUPER_PRESSED__(m_mods);
	}

	// Joystick event
	JoystickEvent::JoystickEvent(GLFWwindow* window, const int joystick, const int event)
		: m_window{window},
		m_joystick{joystick},
		m_event{event}
	{
	}

	JoystickEvent::~JoystickEvent()
	{
	}

	void JoystickEvent::Print() const
	{
		printf("Joystick event: joystick:%d, event:%d\n", m_joystick, m_event);
	}

	// Key pressed
	KeyEvent::KeyEvent(GLFWwindow* window, const int key, const int scancode, const int mods, const bool pressed)
		: m_window{window},
		m_key{key},
		m_scancode{scancode},
		m_mods{mods},
		m_pressed{pressed}
	{
	}

	KeyEvent::~KeyEvent()
	{
	}

	void KeyEvent::Print() const
	{
		printf("Key event: key:%d, scancode:%d, mods:%d, released/pressed:%d\n", m_key, m_scancode, m_mods, m_pressed);
	}

	bool KeyEvent::ShiftPressed() const
	{
		return __NGL_SHIFT_PRESSED__(m_mods);
	}

	bool KeyEvent::ControlPressed() const
	{
		return __NGL_CONTROL_PRESSED__(m_mods);
	}

	bool KeyEvent::AltPressed() const
	{
		return __NGL_ALT_PRESSED__(m_mods);
	}

	bool KeyEvent::SuperPressed() const
	{
		return __NGL_SUPER_PRESSED__(m_mods);
	}

	// Text event
	TextEvent::TextEvent(GLFWwindow* window, const unsigned int codepoint, const int mods)
		: m_window{window},
		m_codepoint{codepoint},
		m_mods{mods}
	{
	}

	TextEvent::~TextEvent()
	{
	}

	void TextEvent::Print() const
	{
		printf("Text event: codepoint:%d, mods:%d\n", m_codepoint, m_mods);
	}

	bool TextEvent::ShiftPressed() const
	{
		return __NGL_SHIFT_PRESSED__(m_mods);
	}

	bool TextEvent::ControlPressed() const
	{
		return __NGL_CONTROL_PRESSED__(m_mods);
	}

	bool TextEvent::AltPressed() const
	{
		return __NGL_ALT_PRESSED__(m_mods);
	}

	bool TextEvent::SuperPressed() const
	{
		return __NGL_SUPER_PRESSED__(m_mods);
	}

	// Drop event
	DropEvent::DropEvent(GLFWwindow* window, const int count, const char** paths)
		: m_window{window},
		m_count{count},
		m_paths{paths}
	{
	}

	DropEvent::~DropEvent()
	{
	}

	void DropEvent::Print() const
	{
		printf("Drop event: count:%d\n", m_count);
		for(int i = 0; i < m_count; ++i)
		{
			printf("Path %d: %s\n", i, m_paths[i]);
		}
	}

	// Resize event
	ResizeEvent::ResizeEvent(GLFWwindow* window, const int width, const int height)
		: m_window{window},
		m_width{width},
		m_height{height}
	{
	}

	ResizeEvent::~ResizeEvent()
	{
	}

	void ResizeEvent::Print() const
	{
		printf("Resize event: width:%d, height:%d\n", m_width, m_height);
	}

	// Focus event
	FocusEvent::FocusEvent(GLFWwindow* window, const bool focused)
		: m_window{window},
		m_focused{focused}
	{
	}

	FocusEvent::~FocusEvent()
	{
	}

	void FocusEvent::Print() const
	{
		printf("Focus event: focused:%d\n", m_focused);
	}

	// Closed event
	ClosedEvent::ClosedEvent(GLFWwindow* window)
		: m_window{window}
	{
	}

	ClosedEvent::~ClosedEvent()
	{
	}

	void ClosedEvent::Print() const
	{
		printf("Closed event\n");
	}

	// Input event
	InputEvent::InputEvent(const InputType type)
		: m_type{type}
	{
	}

	void InputEvent::Print() const
	{
		switch(m_type)
		{
			case InputType::mouse_move:
				m_event.m_move.Print();
				break;
			case InputType::mouse_drag:
				m_event.m_drag.Print();
			case InputType::mouse_scroll:
				m_event.m_scroll.Print();
				break;
			case InputType::mouse_enter:
			case InputType::mouse_left:
				m_event.m_entered.Print();
				break;
			case InputType::mouse_button_pressed:
			case InputType::mouse_button_released:
				m_event.m_mouse.Print();
				break;
			case InputType::joystick:
				m_event.m_joystick.Print();
				break;
			case InputType::key_pressed:
			case InputType::key_released:
				m_event.m_key.Print();
				break;
			case InputType::text:
				m_event.m_text.Print();
				break;
			case InputType::drop:
				m_event.m_drop.Print();
				break;
			case InputType::resize:
				m_event.m_resize.Print();
				break;
			case InputType::lost_focus:
			case InputType::gained_focus:
				m_event.m_focus.Print();
				break;
			case InputType::closed:
				m_event.m_closed.Print();
				break;
			default:
				printf("InputEvent::Print: Input type doesn't exist #%d\n", m_type);
				break;
		}
	}
}