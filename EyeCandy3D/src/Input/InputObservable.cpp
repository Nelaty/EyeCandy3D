#include "EC3D/Input/InputObservable.h"
#include "EC3D/Input/InputListener.h"

#include <algorithm>
#include <GLFW/glfw3.h>

namespace ec
{	
	InputObservable::~InputObservable()
	= default;

	void InputObservable::receiveEvent(const InputEvent& event)
	{
		const auto preparedEvent = prepareEvent(event);
		for(auto& controller : m_inputListeners)
		{
			controller->inform(preparedEvent);
		}
	}

	void InputObservable::registerInputListener(InputListener* inputListener)
	{
		if(!contains(inputListener))
		{
			m_inputListeners.push_back(inputListener);
		}
	}

	bool InputObservable::unregisterInputListener(InputListener* inputListener)
	{
		const auto foundListener = std::remove(m_inputListeners.begin(),
											   m_inputListeners.end(),
											   inputListener);

		return foundListener != m_inputListeners.end();
	}

	bool InputObservable::contains(InputListener* inputListener)
	{
		const auto foundListener = std::find(m_inputListeners.begin(),
											 m_inputListeners.end(),
											 inputListener);

		return foundListener != m_inputListeners.end();
	}

	void InputObservable::unregisterAllInputListeners()
	{
		m_inputListeners = InputListeners_Type();
	}

	void InputObservable::informAll()
	{
		/// \todo: not even doing anything
		for(const auto& event : m_events)
		{
			for(auto& controller : m_inputListeners)
			{
				controller->inform(event);
			}
		}
		clearEvents();
	}

	void InputObservable::setPrevMouseEvent(const MouseEvent& event)
	{
		m_prevMouseEvent = event;
	}

	const ec::MouseEvent& InputObservable::getPrevMouseEvent() const
	{
		return m_prevMouseEvent;
	}

	void InputObservable::setPrevKeyboardEvent(const KeyboardEvent& event)
	{
		m_prevKeyboardEvent = event;
	}

	const ec::KeyboardEvent& InputObservable::getPrevKeyboardEvent() const
	{
		return m_prevKeyboardEvent;
	}

	void InputObservable::setPrevDisplayEvent(const DisplayEvent& event)
	{
		m_prevDisplayEvent = event;
	}

	const ec::DisplayEvent& InputObservable::getPrevDisplayEvent() const
	{
		return m_prevDisplayEvent;
	}

	ec::InputEvent InputObservable::prepareEvent(const InputEvent& event)
	{
		auto preparedEvent = event;

		preparedEvent.m_timestamp = glfwGetTime();
	
		switch(event.m_type)
		{
			case InputType::mouse_move:
			{
				auto& mouseEvent = preparedEvent.m_event.m_mouse;
				mouseEvent.m_dx = mouseEvent.m_x - m_prevMouseEvent.m_x;
				mouseEvent.m_dy = mouseEvent.m_y - m_prevMouseEvent.m_y;
				mouseEvent.m_button = m_prevMouseEvent.m_button;
				mouseEvent.m_mods = m_prevMouseEvent.m_mods;
				mouseEvent.m_pressure = m_prevMouseEvent.m_pressure;

				setPrevMouseEvent(event.m_event.m_mouse);
				break;
			}
			case InputType::mouse_button_released:
			case InputType::mouse_button_pressed:
			{
				auto& mouseEvent = preparedEvent.m_event.m_mouse;
				mouseEvent.m_x = m_prevMouseEvent.m_x;
				mouseEvent.m_y = m_prevMouseEvent.m_y;

				setPrevMouseEvent(event.m_event.m_mouse);
				break;
			}
			case InputType::key_pressed:
			case InputType::key_released:
			{
				setPrevKeyboardEvent(event.m_event.m_keyboard);
				break;
			}
			case InputType::text:
			{
				setPrevKeyboardEvent(event.m_event.m_keyboard);
				break;
			}

			case InputType::gained_focus:
			case InputType::lost_focus:
			{
				setPrevDisplayEvent(event.m_event.m_display);
				break;
			}


			default:
			{
				break;
			}
		}

		return preparedEvent;
	}

	void InputObservable::clearEvents()
	{
		m_events = Events_Type();
	}

	InputObservable::InputObservable()
	= default;
}
