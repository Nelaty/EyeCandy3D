#include "EC3D/Core/InputObservable.h"
#include "EC3D/Core/InputListener.h"

#include <algorithm>

namespace ec
{	
	InputObservable::~InputObservable()
	{
	}

	void InputObservable::ReceiveEvent(const InputEvent& event)
	{
		InputEvent preparedEvent = PrepareEvent(event);
		for(auto& controller : m_inputListeners)
		{
			controller->Inform(preparedEvent);
		}
	}

	void InputObservable::RegisterInputListener(InputListener* inputListener)
	{
		if(!Contains(inputListener))
		{
			m_inputListeners.push_back(inputListener);
		}
	}

	bool InputObservable::UnregisterInputListener(InputListener* inputListener)
	{
		auto foundListener = std::remove(m_inputListeners.begin(),
										 m_inputListeners.end(),
										 inputListener);

		return foundListener != m_inputListeners.end();
	}

	bool InputObservable::Contains(InputListener* inputListener)
	{
		auto foundListener = std::find(m_inputListeners.begin(),
									   m_inputListeners.end(),
									   inputListener);

		return foundListener != m_inputListeners.end();
	}

	void InputObservable::UnregisterAllInputListeners()
	{
		m_inputListeners = InputListeners_T();
	}

	void InputObservable::InformAll()
	{
		for(const auto& event : m_events)
		{
			for(auto& controller : m_inputListeners)
			{
				controller->Inform(event);
			}
		}
		ClearEvents();
	}

	void InputObservable::SetLastPrevMouseEvent(const MouseEvent& event)
	{
		m_prevMouseEvent = event;
	}

	const ec::MouseEvent& InputObservable::GetPrevMouseEvent() const
	{
		return m_prevMouseEvent;
	}

	void InputObservable::SetPrevKeyboardEvent(const KeyboardEvent& event)
	{
		m_prevKeyboardEvent = event;
	}

	const ec::KeyboardEvent& InputObservable::GetPrevKeyboardEvent() const
	{
		return m_prevKeyboardEvent;
	}

	void InputObservable::SetPrevDisplayEvent(const DisplayEvent& event)
	{
		m_prevDisplayEvent = event;
	}

	const ec::DisplayEvent& InputObservable::GetPrevDisplayEvent() const
	{
		return m_prevDisplayEvent;
	}

	ec::InputEvent InputObservable::PrepareEvent(const InputEvent& event)
	{
		InputEvent result = event;

		switch(event.m_type)
		{
			case InputType::mouse_move:
			{
				SetLastPrevMouseEvent(event.m_event.m_mouse);
				break;
			}
			case InputType::mouse_button_released:
			case InputType::mouse_button_pressed:
			{
				SetLastPrevMouseEvent(event.m_event.m_mouse);
				break;
			}
			case InputType::key_pressed:
			case InputType::key_released:
			{
				SetPrevKeyboardEvent(event.m_event.m_keyboard);
				break;
			}
			case InputType::text:
			{
				SetPrevKeyboardEvent(event.m_event.m_keyboard);
				break;
			}

			case InputType::gained_focus:
			case InputType::lost_focus:
			{
				SetPrevDisplayEvent(event.m_event.m_display);
				break;
			}


			default:
			{
				break;
			}
		}

		return result;
	}

	void InputObservable::ClearEvents()
	{
		m_events = Events_T();
	}

	InputObservable::InputObservable()
	{
	}
}