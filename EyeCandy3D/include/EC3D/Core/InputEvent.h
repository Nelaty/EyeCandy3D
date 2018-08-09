#pragma once

struct GLFWwindow;

namespace ec
{
	/*
	* Enumeration entries for every kind of input event
	*/
	enum class InputType : unsigned char
	{
		mouse_move = 0,
		mouse_drag,
		mouse_scroll,
		mouse_enter,
		mouse_left,
		mouse_button_pressed,
		mouse_button_released,

		joystick,

		key_pressed,
		key_released,
		text,

		drop,
		resize,
		lost_focus,
		gained_focus,
		closed,

		count // Keep at end! - Number of event types
	};

	struct MouseMoveEvent
	{
		MouseMoveEvent(GLFWwindow* window, const float x, const float y);
		~MouseMoveEvent();

		void Print() const;

		GLFWwindow* m_window;
		float m_x;
		float m_y;
	};

	struct MouseDragEvent
	{
		MouseDragEvent(GLFWwindow* window, const float offsetX, const float offsetY, const float x, const float y, const int button, const int modifier);
		~MouseDragEvent();

		void Print() const;

		GLFWwindow* m_window;
		float m_x;
		float m_y;
		float m_offsetX;
		float m_offsetY;
		int m_button;
		int m_modifier;

		bool ShiftPressed() const;
		bool ControlPressed() const;
		bool AltPressed() const;
		bool SuperPressed() const;
	};

	struct MouseScrollEvent
	{
		MouseScrollEvent(GLFWwindow* window, const float offsetX, const float offsetY);
		~MouseScrollEvent();

		void Print() const;

		GLFWwindow* m_window;
		float m_offsetX;
		float m_offsetY;
	};

	struct MouseEnterEvent
	{
		MouseEnterEvent(GLFWwindow* window, const bool entered);
		~MouseEnterEvent();

		void Print() const;

		GLFWwindow* m_window;
		bool m_entered;
	};

	struct MouseButtonEvent
	{
		MouseButtonEvent(GLFWwindow* window, const int button, const int mods, const bool pressed);
		~MouseButtonEvent();

		void Print() const;

		GLFWwindow* m_window;
		int m_button;
		int m_mods;
		bool m_pressed;

		bool ShiftPressed() const;
		bool ControlPressed() const;
		bool AltPressed() const;
		bool SuperPressed() const;
	};

	struct JoystickEvent
	{
		JoystickEvent(GLFWwindow* window, const int joystick, const int event);
		~JoystickEvent();

		void Print() const;

		GLFWwindow* m_window;
		int m_joystick;
		int m_event;
	};

	struct KeyEvent
	{
		KeyEvent(GLFWwindow* window, const int key, const int scancode, const int mods, const bool pressed);
		~KeyEvent();

		void Print() const;

		GLFWwindow* m_window;
		int m_key;
		int m_scancode;
		int m_mods;
		bool m_pressed;

		bool ShiftPressed() const;
		bool ControlPressed() const;
		bool AltPressed() const;
		bool SuperPressed() const;
	};

	struct TextEvent
	{
		TextEvent(GLFWwindow* window, const unsigned int codepoint, const int mods);
		~TextEvent();

		void Print() const;

		GLFWwindow* m_window;
		unsigned int m_codepoint;
		int m_mods;

		bool ShiftPressed() const;
		bool ControlPressed() const;
		bool AltPressed() const;
		bool SuperPressed() const;
	};

	struct DropEvent
	{
		DropEvent(GLFWwindow* window, const int count, const char** paths);
		~DropEvent();

		void Print() const;

		GLFWwindow* m_window;
		int m_count;
		const char** m_paths;
	};

	struct ResizeEvent
	{
		ResizeEvent(GLFWwindow* window, const int width, const int height);
		~ResizeEvent();

		void Print() const;

		GLFWwindow* m_window;
		int m_width;
		int m_height;
	};

	struct FocusEvent
	{
		FocusEvent(GLFWwindow* window, const bool focused);
		~FocusEvent();

		void Print() const;

		GLFWwindow* m_window;
		bool m_focused;
	};

	struct ClosedEvent
	{
		ClosedEvent(GLFWwindow* window);
		~ClosedEvent();

		void Print() const;

		GLFWwindow* m_window;
	};

	/*
	* Group all input events to make transfer easy and save memory 
	* by only holding the event, which is currently active
	*/
	struct InputEvent
	{
		explicit InputEvent(const InputType type);

		/* Print the currently active event */
		void Print() const;

		/* Tells which event is currently active */
		InputType m_type;

		union EventData
		{
			EventData(){}
			~EventData(){}

			MouseMoveEvent m_move;
			MouseDragEvent m_drag;
			MouseScrollEvent m_scroll;
			MouseEnterEvent m_entered;
			MouseButtonEvent m_mouse;

			JoystickEvent m_joystick;

			KeyEvent m_key;
			TextEvent m_text;

			DropEvent m_drop;
			ResizeEvent m_resize;
			FocusEvent m_focus;
			ClosedEvent m_closed;
		} m_event;
	};
}