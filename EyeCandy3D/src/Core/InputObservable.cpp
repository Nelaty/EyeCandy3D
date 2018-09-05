#include "EC3D/Core/InputObservable.h"
#include "EC3D/Core/InputListener.h"

#include <algorithm>

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
		for(const auto& event : m_events)
		{
			for(auto& controller : m_inputListeners)
			{
				controller->inform(event);
			}
		}
		clearEvents();
	}

	void InputObservable::setLastPrevMouseEvent(const MouseEvent& event)
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
		auto result = event;

		switch(event.m_type)
		{
			case InputType::mouse_move:
			{
				setLastPrevMouseEvent(event.m_event.m_mouse);
				break;
			}
			case InputType::mouse_button_released:
			case InputType::mouse_button_pressed:
			{
				setLastPrevMouseEvent(event.m_event.m_mouse);
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

		return result;
	}

	void InputObservable::clearEvents()
	{
		m_events = Events_Type();
	}

	InputObservable::InputObservable()
	= default;
}
