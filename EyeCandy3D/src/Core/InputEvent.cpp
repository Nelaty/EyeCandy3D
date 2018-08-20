#include "EC3D/Core/InputEvent.h"
#include <GLFW/glfw3.h>

#include <stdio.h>

#define EC3D_SHIFT_PRESSED(mods) ((GLFW_MOD_SHIFT & (mods)) != 0)
#define EC3D_CONTROL_PRESSED(mods) ((GLFW_MOD_CONTROL & (mods)) != 0)
#define EC3D_ALT_PRESSED(mods) ((GLFW_MOD_ALT & (mods)) != 0)
#define EC3D_SUPER_PRESSED(mods) ((GLFW_MOD_SUPER & (mods)) != 0)

namespace ec
{
	// Joystick event
	JoystickEvent::JoystickEvent(GLFWwindow* window, const int joystick, const int event)
		: m_window{window},
		m_joystick{joystick},
		m_event{event}
	{
	}

	JoystickEvent::JoystickEvent()
		: m_window{nullptr},
		m_joystick{0},
		m_event{0}
	{
	}

	JoystickEvent::~JoystickEvent()
	{
	}

	void JoystickEvent::Print() const
	{
		printf("Joystick event: joystick:%d, event:%d\n", m_joystick, m_event);
	}

	
	// Input event
	InputEvent::InputEvent(const InputType type)
		: m_type{type}
	{
	}

	InputEvent::InputEvent()
	{
	}

	void InputEvent::Print() const
	{
		switch(m_type)
		{
			case InputType::mouse_move:
			case InputType::mouse_scroll:
			case InputType::mouse_enter:
			case InputType::mouse_left:
			case InputType::mouse_button_pressed:
			case InputType::mouse_button_released:
				m_event.m_mouse.Print();
				break;
			case InputType::joystick:
				m_event.m_joystick.Print();
				break;
			case InputType::key_pressed:
			case InputType::key_released:
			case InputType::text:
				m_event.m_keyboard.Print();
				break;
			case InputType::drop:
				m_event.m_drop.Print();
				break;
			case InputType::resize:
			case InputType::lost_focus:
			case InputType::gained_focus:
				m_event.m_display.Print();
				break;
			default:
				printf("InputEvent::Print: Input type doesn't exist #%d\n", m_type);
				break;
		}
	}

	DisplayEvent::DisplayEvent()
		: m_window{nullptr},
		m_x{0},
		m_y{0},
		m_width{0},
		m_height{0},
		m_orientation{DisplayOrientation::rotated_0}
	{
	}

	DisplayEvent::DisplayEvent(GLFWwindow* window,
							   int x, int y, 
							   int width, int height,
							   DisplayOrientation orientation)
		: m_window{window},
		m_x{x},
		m_y{y},
		m_width{width},
		m_height{height},
		m_orientation{orientation}
	{
	}

	void DisplayEvent::Print() const
	{
		printf("DISPLAY EVENT:\n");
		printf("position: (%d, %d), size: (%d, %d), orientation: %d\n",
			   m_x, m_y, m_width, m_height, (int)m_orientation);
	}

	KeyboardEvent::KeyboardEvent()
		: m_window{nullptr},
		m_key{0},
		m_scancode{0},
		m_unicode{0},
		m_mods{0},
		m_repeat{false}
	{
	}

	KeyboardEvent::KeyboardEvent(GLFWwindow* window, 
								 int key, 
								 int scancode,
								 unsigned int unicode,
								 int mods, 
								 bool repeat)
		: m_window{window},
		m_key{key},
		m_scancode{scancode},
		m_unicode{unicode},
		m_mods{mods},
		m_repeat{repeat}
	{
	}

	KeyboardEvent::~KeyboardEvent()
	{
	}

	void KeyboardEvent::Print() const
	{
		printf("KEYBOARD EVENT:\n");
		printf("Window: %d\n", m_window);
		printf("Key: %d, Scancode: %d, Repeat %s",
			   m_key, m_scancode, m_repeat ? "true" : "false");
		printf("Shift:   %s, ", ShiftPressed() ? "true" : "false");
		printf("Control: %s, ", ControlPressed() ? "true" : "false");
		printf("Alt:     %s, ", AltPressed() ? "true" : "false");
		printf("Super:   %s, ", SuperPressed() ? "true" : "false");
	}

	bool KeyboardEvent::ShiftPressed() const
	{
		return EC3D_SHIFT_PRESSED(m_mods);
	}

	bool KeyboardEvent::ControlPressed() const
	{
		return EC3D_CONTROL_PRESSED(m_mods);
	}

	bool KeyboardEvent::AltPressed() const
	{
		return EC3D_ALT_PRESSED(m_mods);
	}

	bool KeyboardEvent::SuperPressed() const
	{
		return EC3D_SUPER_PRESSED(m_mods);
	}

	MouseEvent::MouseEvent()
		: m_window{nullptr},
		m_x{0},
		m_y{0},
		m_z{0},
		m_w{0},
		m_dx{0},
		m_dy{0},
		m_scrollX{0},
		m_scrollY{0},
		m_button{0},
		m_mods{0},
		m_pressure{0.0f}
	{
	}

	MouseEvent::MouseEvent(GLFWwindow* window, 
						   int x, int y, int z, int w,
						   int dx, int dy, int dz, int dw,
						   unsigned int button, 
						   int modifier, 
						   float pressure)
		: m_window{window},
		m_x{x},
		m_y{y},
		m_z{z},
		m_w{w},
		m_dx{dx},
		m_dy{dy},
		m_scrollX{dz},
		m_scrollY{dw},
		m_button{button},
		m_mods{modifier},
		m_pressure{pressure}
	{
	}

	MouseEvent::~MouseEvent()
	{
	}

	void MouseEvent::Print() const
	{
		printf("MOUSE EVENT:\n");
		printf("Window: %d\n", m_window);
		printf("Position: (%d,%d,%d,%d), Position-Delta: (%d,%d,%d,%d)\n",
			   m_x, m_y, m_z, m_w, m_dx, m_dy, m_scrollX, m_scrollY);
		printf("Button: %d, Pressure: %f", m_button, m_pressure);
		printf("Shift:   %s, ", ShiftPressed() ? "true" : "false");
		printf("Control: %s, ", ControlPressed() ? "true" : "false");
		printf("Alt:     %s, ", AltPressed() ? "true" : "false");
		printf("Super:   %s, ", SuperPressed() ? "true" : "false");
	}

	bool MouseEvent::ShiftPressed() const
	{
		return EC3D_SHIFT_PRESSED(m_mods);
	}

	bool MouseEvent::ControlPressed() const
	{
		return EC3D_CONTROL_PRESSED(m_mods);
	}

	bool MouseEvent::AltPressed() const
	{
		return EC3D_ALT_PRESSED(m_mods);
	}

	bool MouseEvent::SuperPressed() const
	{
		return EC3D_SUPER_PRESSED(m_mods);
	}

	DropEvent::DropEvent()
		: m_x{0},
		m_y{0},
		m_window{nullptr},
		m_count{0},
		m_paths{nullptr}
	{
	}

	DropEvent::DropEvent(int x, int y, GLFWwindow* window, const int count, const char** paths)
		: m_x{x},
		m_y{y},
		m_window{window},
		m_count{count},
		m_paths{paths}
	{
	}

	DropEvent::~DropEvent()
	{
	}

	void DropEvent::Print() const
	{
		printf("DROP EVENT\n");
		printf("Window: %d\n", m_window);
		printf("Position: (%d,%d), Count: %d, Paths: \n");
		for(int i = 0; i < m_count; ++i)
		{
			printf("%s\n", m_paths[i]);
		}
	}

}