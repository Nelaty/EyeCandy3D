#include "EC3D/GUI/Backend/OpenGLInput.h"

#include <GLFW/glfw3.h>

namespace agui
{
	
	OpenGLInput::OpenGLInput()
		: shift{false},
		control{false},
		alt{false},
		meta{false}
	{
	}

	OpenGLInput::~OpenGLInput()
	= default;

	double OpenGLInput::getTime() const
	{
		return glfwGetTime();
	}

	void OpenGLInput::processEvent(const ec::InputEvent &event)
	{
		switch(event.m_type)
		{
			case ec::InputType::mouse_button_pressed:
			case ec::InputType::mouse_button_released:
			case ec::InputType::mouse_move:
			case ec::InputType::mouse_scroll:
			{
				if(isMouseEnabled())
				{
					pushMouseEvent(createMouse(event));
				}
				break;
			}
			case ec::InputType::key_pressed:
			case ec::InputType::text:
			{
				if(event.m_event.m_keyboard.shiftPressed())
				{
					this->shift = true;
				}
				if(event.m_event.m_keyboard.controlPressed())
				{
					this->control = true;
				}
				if(event.m_event.m_keyboard.altPressed())
				{
					this->alt = true;
				}
				if(event.m_event.m_keyboard.superPressed())
				{
					this->meta = true;
				}

				if(event.m_type == ec::InputType::key_pressed
				   && !isModifierKey(event.m_event.m_keyboard.m_key))
				{
					break;
				}
				if(isKeyboardEnabled())
				{
					pushKeyboardEvent(createKeyboard(event.m_event.m_keyboard,
													 true,
													 event.m_type == ec::InputType::text));
				}

				break;
			}
			case ec::InputType::key_released:
			{
				if(event.m_event.m_keyboard.shiftPressed())
				{
					this->shift = false;
				}
				if(event.m_event.m_keyboard.controlPressed())
				{
					this->control = false;
				}
				if(event.m_event.m_keyboard.altPressed())
				{
					this->alt = false;
				}
				if(event.m_event.m_keyboard.superPressed())
				{
					this->meta = false;
				}

				if(isKeyboardEnabled())
				{
					pushKeyboardEvent(createKeyboard(event.m_event.m_keyboard,
													 false,
													 false));
				}

				break;
			}
			case ec::InputType::gained_focus:
			{
				this->shift = false;
				this->control = false;
				this->alt = false;
				this->meta = false;
				break;
			}
			default:
			{
				break;
			}
		}
	}

	/*agui::MouseInput OpenGLInput::createMouse(const ec::InputEvent& event)
	{

	}

	agui::KeyboardInput OpenGLInput::createKeyboard(const ec::KeyEvent& event,
													bool isKeyDown,
													bool isRepeat)
	{

	}

	agui::ExtendedKeyEnum OpenGLInput::getExtendedKey(int key) const
	{

	}

	bool OpenGLInput::isModifierKey(int key)
	{

	}

	agui::KeyEnum OpenGLInput::getKeyFromKeycode(int keycode) const
	{

	}*/

}