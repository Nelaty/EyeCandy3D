#pragma once
#include "EC3D/Common/Common.h"
#include "InputEvent.h"

#include <vector>

namespace ec
{
	class Window;
	class InputListener;

	/**
	* \brief InputObservables inform InputListeners about InputEvents
	*/
	class EC3D_DECLSPEC InputObservable
	{
	public:
		using InputListeners_Type = std::vector<InputListener*>;
		using Events_Type = std::vector<InputEvent>;


		explicit InputObservable(Window* window);
		virtual ~InputObservable();

		/**
		* \brief Inform the listeners about a new event.
		* \param event The event to inform about.
		* \detailsThe input observable can't check for inputs itself because
		* of the way GLFW works.
		*/
		virtual void receiveEvent(const InputEvent& event);

		/** 
		 * \brief Register a new input listener.
		 * \param inputListener The input listener to register.
		 */
		virtual void registerInputListener(InputListener* inputListener);
		/**
		 * \brief Unregister an already registered input listener.
		 * \param inputListener The input listener to unregister.
		 * \return True if the inputListener was found, false
		 * otherwise.
		 */
		virtual bool unregisterInputListener(InputListener* inputListener);

		/** 
		 * \brief Check if this observer contains a given controller.
		 * \param inputListener The input listener to search for.
		 * \return True if the inputListener was found. 
		 */
		virtual bool contains(InputListener* inputListener);

		/**
		 * \brief Clears the input listener list. 
		 */
		virtual void unregisterAllInputListeners();

		/** 
		 * \brief Inform all input listeners about all accumulated events.
		 */
		virtual void informAll();

		/**
		 * \brief Set the previous mouse event.
		 */
		void setPrevMouseEvent(const MouseEvent& event);
		/**
		 * \brief Get the previous mouse event.
		 */
		const MouseEvent& getPrevMouseEvent() const;

		/** 
		 * \brief Set the previous keyboard event.
		 */
		void setPrevKeyboardEvent(const KeyboardEvent& event);
		/** 
		 * \brief Get the previous keyboard event.
		 */
		const KeyboardEvent& getPrevKeyboardEvent() const;

		/** 
		 * \brief Set the previous keyboard event.
		 */
		void setPrevDisplayEvent(const DisplayEvent& event);
		/** 
		 * \brief Get the previous keyboard event.
		 */
		const DisplayEvent& getPrevDisplayEvent() const;

	protected:
		InputEvent prepareEvent(const InputEvent& event);

		Window* m_window{};

		InputListeners_Type m_inputListeners;
		Events_Type m_events;

		MouseEvent m_prevMouseEvent;
		KeyboardEvent m_prevKeyboardEvent;
		DisplayEvent m_prevDisplayEvent;

		virtual void clearEvents();
	};
}