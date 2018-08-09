#pragma once
#include "InputEvent.h"

#include <vector>
#include <glm/glm.hpp>

/*
* Observer pattern
* InputObservables inform InputObservers about InputEvents
*/
namespace ec
{
	class InputListener;

	class InputObservable
	{
	public:
		using InputControllers_T = std::vector<InputListener*>;
		using Events_T = std::vector<InputEvent>;
	public:
		explicit InputObservable();
		virtual ~InputObservable();

		/* 
		* Inform the observer about a new event
		* The input observer can't check for inputs itself because of the way GLFW works
		*/
		virtual void ReceiveEvent(const InputEvent& event);

		/* Register a new or remove an old controller */
		virtual void RegisterInputController(InputListener* inputController);
		virtual bool UnregisterInputController(InputListener* inputController);

		/* Check if this observer contains a specific controller */
		virtual bool Contains(InputListener* inputController);

		/* Clears the input controller list */
		virtual void UnregisterAllInputControllers();

		/* Inform all input controllers about all accumulated events */
		virtual void InformAll();

		/* Meta state, which is needed for drag events */
		void SetLastMouseButtonEvent(const MouseButtonEvent& event);
		const MouseButtonEvent& GetLastMouseButtonEvent() const;

		void SetLastMousePosition(const glm::vec2& position);
		const glm::vec2 GetLastMousePosition() const;

	protected:
		InputControllers_T m_inputController;
		Events_T m_events;

		/* Previous mouse events  */
		MouseButtonEvent m_lastMouseButtonEvent;
		glm::vec2 m_lastMousePosition;

		virtual void ClearEvents();
	};
}