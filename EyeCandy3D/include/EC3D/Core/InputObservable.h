#pragma once
#include "InputEvent.h"

#include <vector>
#include <glm/glm.hpp>

/*
* InputObservables inform InputObservers about InputEvents
*/
namespace ec
{
	class InputListener;

	class InputObservable
	{
	public:
		using InputListeners_T = std::vector<InputListener*>;
		using Events_T = std::vector<InputEvent>;
	public:
		explicit InputObservable();
		virtual ~InputObservable();

		/* 
		* Inform the listeners about a new event
		* The input listener can't check for inputs itself because of the way GLFW works
		*/
		virtual void ReceiveEvent(const InputEvent& event);

		/* Register a new or remove an old listener */
		virtual void RegisterInputListener(InputListener* inputListener);
		virtual bool UnregisterInputListener(InputListener* inputListener);

		/* Check if this observer contains a specific controller */
		virtual bool Contains(InputListener* inputListener);

		/* Clears the input listener list */
		virtual void UnregisterAllInputListeners();

		/* Inform all input listeners about all accumulated events */
		virtual void InformAll();

		/* Meta state, which is needed for drag events */
		void SetLastMouseButtonEvent(const MouseButtonEvent& event);
		const MouseButtonEvent& GetLastMouseButtonEvent() const;

		void SetLastMousePosition(const glm::vec2& position);
		const glm::vec2 GetLastMousePosition() const;

	protected:
		InputListeners_T m_inputListeners;
		Events_T m_events;

		/* Previous mouse events  */
		MouseButtonEvent m_lastMouseButtonEvent;
		glm::vec2 m_lastMousePosition;

		virtual void ClearEvents();
	};
}