#pragma once
#include "EC3D/Core/Input/InputEvent.h"

#include <vector>

namespace ec
{
	class InputListener;

	class EventProcessor
	{
	public:
		explicit EventProcessor();
		~EventProcessor();

		using InputListeners_Type = std::vector<InputListener*>;

		/** \brief Inform the listeners about a new event.
		* \param event The event to inform about. */
		void receiveEvent(const InputEvent& event);

		/** \brief Register a new input listener.
		* \param inputListener The input listener to register. */
		void registerInputListener(InputListener* inputListener);
		/** \brief Unregister an already registered input listener.
		* \param inputListener The input listener to unregister.
		* \return True if the inputListener was found, false
		* otherwise. */
		bool unregisterInputListener(InputListener* inputListener);

		/** \brief Check if this event processor contains a given controller.
		* \param inputListener The input listener to search for.
		* \return True if the inputListener was found.	*/
		bool contains(InputListener* inputListener);

		/** \brief Clears the input listener list. */
		void unregisterAllInputListeners();

	protected:
		InputListeners_Type m_inputListeners;
	};
}