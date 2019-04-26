#pragma once
#include "EC3D/Common/Common.h"

#include "InputObservable.h"
#include "DeviceRegistry.h"

namespace ec
{
	class Window;

	/**
	 * \brief Responsible for the distribution of input events.
	 */
	class EC3D_DECLSPEC EventSystem
	{
	public:
		explicit EventSystem(Window* window);
		~EventSystem();

		/**
		 * \brief Inform event system about a new event.
		 * \param event The new event.
		 */
		void dispatchEvent(const InputEvent& event);

		/**
		 * \brief Inform input listeners about new events.
		 */
		void informAll();

		/** 
		 * \brief Register an input listener.
		 * \param inputListener The new input listener.
		 */
		void registerInputListener(InputListener* inputListener);
		/**
		 * \brief Register an already registered input listener.
		 * \param inputListener The input listener to remove.
		 * \return True if the input listener was found, false otherwise.
		 */
		bool unregisterInputListener(InputListener* inputListener);

		/** 
		 * \brief Check if this observer contains a specific input listener.
		 * \param inputListener The input listener to find.
		 * \return True if the given listener is registered, false
		 * otherwise.
		 */
		bool contains(InputListener* inputListener);

		/** 
		 * \brief Clears the input listener list.
		 */
		void unregisterAllInputListeners();

		/** 
		 * \brief Check the event queue for new events and inform the
		 * event observable about them.
		 */
		void pollEvents();

		/** 
		 * \brief Get the window from which this event system receives 
		 * its events.
		 */
		Window* getWindow() const;

		/** 
		 * \brief Get the device registry storing the input devices. 
		 */
		DeviceRegistry& getDeviceRegistry();

	private:
		Window* m_window;

		DeviceRegistry m_deviceRegistry;
		InputObservable m_inputObservable;
	};
}
