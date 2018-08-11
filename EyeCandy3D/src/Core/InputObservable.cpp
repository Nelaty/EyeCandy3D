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
		for(auto& controller : m_inputListeners)
		{
			controller->Inform(event);
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

	void InputObservable::SetLastMouseButtonEvent(const MouseButtonEvent& event)
	{
		m_lastMouseButtonEvent = event;
	}

	const ec::MouseButtonEvent& InputObservable::GetLastMouseButtonEvent() const
	{
		return m_lastMouseButtonEvent;
	}

	void InputObservable::SetLastMousePosition(const glm::vec2& position)
	{
		m_lastMousePosition = position;
	}

	const glm::vec2 InputObservable::GetLastMousePosition() const
	{
		return m_lastMousePosition;
	}

	void InputObservable::ClearEvents()
	{
		m_events = Events_T();
	}

	InputObservable::InputObservable()
		: m_lastMouseButtonEvent(nullptr, 0, 0, false)
	{
	}
}