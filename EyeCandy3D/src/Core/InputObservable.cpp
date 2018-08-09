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
		for(auto& controller : m_inputController)
		{
			controller->Inform(event);
		}
	}

	void InputObservable::RegisterInputController(InputListener* inputController)
	{
		if(!Contains(inputController))
		{
			m_inputController.push_back(inputController);
		}
	}

	bool InputObservable::UnregisterInputController(InputListener* inputController)
	{
		auto foundController = std::remove(m_inputController.begin(),
										   m_inputController.end(),
										   inputController);

		return foundController != m_inputController.end();
	}

	bool InputObservable::Contains(InputListener* inputController)
	{
		auto foundController = std::find(m_inputController.begin(),
										 m_inputController.end(),
										 inputController);

		return foundController != m_inputController.end();
	}

	void InputObservable::UnregisterAllInputControllers()
	{
		m_inputController = InputControllers_T();
	}

	void InputObservable::InformAll()
	{
		for(const auto& event : m_events)
		{
			for(auto& controller : m_inputController)
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