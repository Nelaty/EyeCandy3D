#pragma once
#include "InputEvent.h"

#include <vector>
#include <glm/glm.hpp>

/**
* InputObservables inform InputListeners about InputEvents
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

		/* *
		* Inform the listeners about a new event
		* The input listener can't check for inputs itself because of the way GLFW works
		*/
		virtual void ReceiveEvent(const InputEvent& event);

		/** Register a new or remove an old listener */
		virtual void RegisterInputListener(InputListener* inputListener);
		virtual bool UnregisterInputListener(InputListener* inputListener);

		/** Check if this observer contains a specific controller */
		virtual bool Contains(InputListener* inputListener);

		/** Clears the input listener list */
		virtual void UnregisterAllInputListeners();

		/** Inform all input listeners about all accumulated events */
		virtual void InformAll();

		/** Set the previous mouse event */
		void SetLastPrevMouseEvent(const MouseEvent& event);
		/** Get the previous mouse event */
		const MouseEvent& GetPrevMouseEvent() const;

		/** Set the previous keyboard event */
		void SetPrevKeyboardEvent(const KeyboardEvent& event);
		/** Get the previous keyboard event */
		const KeyboardEvent& GetPrevKeyboardEvent() const;

		/** Set the previous keyboard event */
		void SetPrevDisplayEvent(const DisplayEvent& event);
		/** Get the previous keyboard event */
		const DisplayEvent& GetPrevDisplayEvent() const;

	protected:

		InputEvent PrepareEvent(const InputEvent& event);

		InputListeners_T m_inputListeners;
		Events_T m_events;

		/** Previous mouse event */
		MouseEvent m_prevMouseEvent;
		/** Previous keyboard event */
		KeyboardEvent m_prevKeyboardEvent;
		/** Previous display event */
		DisplayEvent m_prevDisplayEvent;

		virtual void ClearEvents();
	};
}