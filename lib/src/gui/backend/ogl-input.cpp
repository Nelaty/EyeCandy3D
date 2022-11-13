#include "ec3/Gui/Backend/OpenGLInput.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ec3/input/mouse.h"
#include "ec3/input/keyboard.h"

namespace ec
{
	
	OpenGLInput::OpenGLInput()
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
					pushMouseEvent(createMouse(event, event.m_type));
				}
				break;
			}
			case ec::InputType::key_pressed:
			case ec::InputType::text:
			{
				if(event.m_type == ec::InputType::key_pressed
				   && !isModifierKey(event.m_event.m_keyboard.m_key))
				{
					break;
				}
				if(isKeyboardEnabled())
				{
					pushKeyboardEvent(createKeyboard(event,
													 event.m_type,
													 true,
													 event.m_type == ec::InputType::text));
				}

				break;
			}
			case ec::InputType::key_released:
			{
				if(isKeyboardEnabled())
				{
					pushKeyboardEvent(createKeyboard(event,
													 event.m_type,
													 false,
													 false));
				}

				break;
			}
			default:
			{
				break;
			}
		}
	}

	agui::MouseInput OpenGLInput::createMouse(const ec::InputEvent& event, InputType inputType)
	{
		const auto& mouseEvent = event.m_event.m_mouse;

		// Get the type of the mouse event
		agui::MouseEvent::MouseEventEnum type;
		switch(inputType)
		{
			case ec::InputType::mouse_button_pressed:
			{
				type = agui::MouseEvent::MOUSE_DOWN;
				break;
			}
			case ec::InputType::mouse_button_released:
			{
				type = agui::MouseEvent::MOUSE_UP;
				break;
			}
			case ec::InputType::mouse_move:
			{
				type = agui::MouseEvent::MOUSE_MOVE;
				break;
			}
			case ec::InputType::mouse_scroll:
			{
				if(mouseEvent.m_dy > 0.0f)
				{
					type = agui::MouseEvent::MOUSE_WHEEL_UP;
				}
				else if(mouseEvent.m_dy > 0.0f)
				{
					type = agui::MouseEvent::MOUSE_WHEEL_DOWN;
				}
				else
				{
					type = agui::MouseEvent::MOUSE_MOVE;
				}
				break;
			}
			default:
			{
				break;
			}
		}

		// Get the pressed mouse button
		agui::MouseButtonEnum button;
		switch(mouseEvent.m_button)
		{
			case Mouse::MOUSE_LEFT:
			{
				button = agui::MOUSE_BUTTON_LEFT;
				break;
			}
			case Mouse::MOUSE_RIGHT:
			{
				button = agui::MOUSE_BUTTON_RIGHT;
				break;
			}
			case Mouse::MOUSE_MIDDLE:
			{
				button = agui::MOUSE_BUTTON_MIDDLE;
				break;
			}
			default:
			{
				button = agui::MOUSE_BUTTON_NONE;
				break;
			}
		}

		// Create new mouse event
		return agui::MouseInput(type,
								button,
								mouseEvent.m_x,
								mouseEvent.m_y,
								mouseEvent.m_dy,
								mouseEvent.m_pressure,
								event.m_timestamp,
								mouseEvent.altPressed(),
								mouseEvent.shiftPressed(),
								mouseEvent.controlPressed());
	}

	agui::KeyboardInput OpenGLInput::createKeyboard(const ec::InputEvent& event, 
													InputType inputType,
													bool isKeyDown,
													bool isRepeat)
	{
		const auto& keyEvent = event.m_event.m_keyboard;

		// Get extended key
		const auto extKey = getExtendedKey(keyEvent.m_key);

		// Get key
		agui::KeyEnum key = getKeyFromKeycode(keyEvent.m_key);

		// Get key type
		agui::KeyEvent::KeyboardEventEnum type;
		if(isRepeat)
		{
			type = agui::KeyEvent::KEY_REPEAT;
		}
		else if(isKeyDown)
		{
			type = agui::KeyEvent::KEY_DOWN;
		}
		else
		{
			type = agui::KeyEvent::KEY_UP;
		}

		// Create new keyboard event
		return agui::KeyboardInput(type,
								   key,
								   extKey,
								   keyEvent.m_unicode,
								   event.m_timestamp,
								   keyEvent.altPressed(),
								   keyEvent.shiftPressed(),
								   keyEvent.controlPressed(),
								   keyEvent.superPressed(),
								   keyEvent.m_key,
								   keyEvent.m_mods);
	}

	agui::ExtendedKeyEnum OpenGLInput::getExtendedKey(const int key)
	{
		agui::ExtendedKeyEnum extKey = agui::EXT_KEY_NONE;
		switch(key)
		{
			case Keyboard::ALT:
				extKey = agui::EXT_KEY_ALT;
				break;
			case Keyboard::SHIFT_LEFT:
				extKey = agui::EXT_KEY_LEFT_SHIFT;
				break;
			case Keyboard::SHIFT_RIGHT:
				extKey = agui::EXT_KEY_RIGHT_SHIFT;
				break;
			case Keyboard::CONTROL_LEFT:
				extKey = agui::EXT_KEY_LEFT_CONTROL;
				break;
			case Keyboard::CONTROL_RIGHT:
				extKey = agui::EXT_KEY_RIGHT_CONTROL;
				break;
			case Keyboard::SUPER_LEFT:
				extKey = agui::EXT_KEY_LEFT_META;
				break;
			case Keyboard::SUPER_RIGHT:
				extKey = agui::EXT_KEY_RIGHT_META;
				break;
			case Keyboard::HOME:
				extKey = agui::EXT_KEY_HOME;
				break;
			case Keyboard::INSERT:
				extKey = agui::EXT_KEY_INSERT;
				break;
			case Keyboard::PAGE_DOWN:
				extKey = agui::EXT_KEY_PAGE_DOWN;
				break;
			case Keyboard::PAGE_UP:
				extKey = agui::EXT_KEY_PAGE_UP;
				break;
			case Keyboard::END:
				extKey = agui::EXT_KEY_END;
				break;
			case Keyboard::CAPS_LOCK:
				extKey = agui::EXT_KEY_CAPS_LOCK;
				break;
			case Keyboard::F1:
				extKey = agui::EXT_KEY_F1;
				break;
			case Keyboard::F2:
				extKey = agui::EXT_KEY_F2;
				break;
			case Keyboard::F3:
				extKey = agui::EXT_KEY_F3;
				break;
			case Keyboard::F4:
				extKey = agui::EXT_KEY_F4;
				break;
			case Keyboard::F5:
				extKey = agui::EXT_KEY_F5;
				break;
			case Keyboard::F6:
				extKey = agui::EXT_KEY_F6;
				break;
			case Keyboard::F7:
				extKey = agui::EXT_KEY_F7;
				break;
			case Keyboard::F8:
				extKey = agui::EXT_KEY_F8;
				break;
			case Keyboard::F9:
				extKey = agui::EXT_KEY_F9;
				break;
			case Keyboard::F10:
				extKey = agui::EXT_KEY_F10;
				break;
			case Keyboard::F11:
				extKey = agui::EXT_KEY_F11;
				break;
			case Keyboard::F12:
				extKey = agui::EXT_KEY_F12;
				break;
			case Keyboard::PRINT_SCREEN:
				extKey = agui::EXT_KEY_PRINT_SCREEN;
				break;
			case Keyboard::SCROLL_LOCK:
				extKey = agui::EXT_KEY_SCROLL_LOCK;
				break;
			case Keyboard::PAUSE:
				extKey = agui::EXT_KEY_PAUSE;
				break;
			case Keyboard::NUM_LOCK:
				extKey = agui::EXT_KEY_NUM_LOCK;
				break;
			case Keyboard::ALT_RIGHT:
				extKey = agui::EXT_KEY_ALTGR;
				break;
			case Keyboard::UP:
				extKey = agui::EXT_KEY_UP;
				break;
			case Keyboard::DOWN:
				extKey = agui::EXT_KEY_DOWN;
				break;
			case Keyboard::LEFT:
				extKey = agui::EXT_KEY_LEFT;
				break;
			case Keyboard::RIGHT:
				extKey = agui::EXT_KEY_RIGHT;
				break;

			default:
				break;
		}
		return extKey;
	}

	bool OpenGLInput::isModifierKey(const int key)
	{
		switch(key)
		{
			case Keyboard::SHIFT:
			case Keyboard::CONTROL:
			case Keyboard::ALT:
			case Keyboard::SUPER:
			case Keyboard::MENU:
			case Keyboard::SCROLL_LOCK:
			case Keyboard::CAPS_LOCK:
			case Keyboard::NUM_LOCK:
				return true;
			default:
				return false;
		}
	}

	agui::KeyEnum OpenGLInput::getKeyFromKeycode(const int keycode)
	{
		agui::KeyEnum k = agui::KEY_NONE;
		switch(keycode)
		{
			case Keyboard::TAB:
				k = agui::KEY_TAB;
				break;
			case Keyboard::ENTER:
				k = agui::KEY_ENTER;
				break;
			case Keyboard::ESCAPE:
				k = agui::KEY_ESCAPE;
				break;
			case Keyboard::SPACE:
				k = agui::KEY_SPACE;
				break;
			/*case Keyboard::TILDE:
				k = agui::KEY_TIDLE;
				break;*/
			case Keyboard::MINUS:
				k = agui::KEY_HYPHEN;
				break;
			case Keyboard::EQUAL:
				k = agui::KEY_EQUALS;
				break;
			case Keyboard::PERIOD:
				k = agui::KEY_PERIOD;
				break;
			case Keyboard::COMMA:
				k = agui::KEY_COMMA;
				break;
			/*case Keyboard::QUOTATION:
				k = agui::KEY_SINGLE_QUOTATION;
				break;*/
			case Keyboard::SLASH:
				k = agui::KEY_FORWARDSLASH;
				break;
			case Keyboard::BACKSLASH:
				k = agui::KEY_BACKSLASH;
				break;
			case Keyboard::LEFT_BRACKET:
				k = agui::KEY_OPEN_BRACE;
				break;
			case Keyboard::RIGHT_BRACKET:
				k = agui::KEY_CLOSING_BRACE;
				break;
			case Keyboard::A:
				k = agui::KEY_A;
				break;
			case Keyboard::B:
				k = agui::KEY_B;
				break;
			case Keyboard::C:
				k = agui::KEY_C;
				break;
			case Keyboard::D:
				k = agui::KEY_D;
				break;
			case Keyboard::E:
				k = agui::KEY_E;
				break;
			case Keyboard::F:
				k = agui::KEY_F;
				break;
			case Keyboard::G:
				k = agui::KEY_G;
				break;
			case Keyboard::H:
				k = agui::KEY_H;
				break;
			case Keyboard::I:
				k = agui::KEY_I;
				break;
			case Keyboard::J:
				k = agui::KEY_J;
				break;
			case Keyboard::K:
				k = agui::KEY_K;
				break;
			case Keyboard::L:
				k = agui::KEY_L;
				break;
			case Keyboard::M:
				k = agui::KEY_M;
				break;
			case Keyboard::N:
				k = agui::KEY_N;
				break;
			case Keyboard::O:
				k = agui::KEY_O;
				break;
			case Keyboard::P:
				k = agui::KEY_P;
				break;
			case Keyboard::Q:
				k = agui::KEY_Q;
				break;
			case Keyboard::R:
				k = agui::KEY_R;
				break;
			case Keyboard::S:
				k = agui::KEY_S;
				break;
			case Keyboard::T:
				k = agui::KEY_T;
				break;
			case Keyboard::U:
				k = agui::KEY_U;
				break;
			case Keyboard::V:
				k = agui::KEY_V;
				break;
			case Keyboard::W:
				k = agui::KEY_W;
				break;
			case Keyboard::X:
				k = agui::KEY_X;
				break;
			case Keyboard::Y:
				k = agui::KEY_Y;
				break;
			case Keyboard::Z:
				k = agui::KEY_Z;
				break;
			case Keyboard::KEY_0:
				k = agui::KEY_0;
				break;
			case Keyboard::KEY_1:
				k = agui::KEY_1;
				break;
			case Keyboard::KEY_2:
				k = agui::KEY_2;
				break;
			case Keyboard::KEY_3:
				k = agui::KEY_3;
				break;
			case Keyboard::KEY_4:
				k = agui::KEY_4;
				break;
			case Keyboard::KEY_5:
				k = agui::KEY_5;
				break;
			case Keyboard::KEY_6:
				k = agui::KEY_6;
				break;
			case Keyboard::KEY_7:
				k = agui::KEY_7;
				break;
			case Keyboard::KEY_8:
				k = agui::KEY_8;
				break;
			case Keyboard::KEY_9:
				k = agui::KEY_9;
				break;
		}
		return k;
	}
}
