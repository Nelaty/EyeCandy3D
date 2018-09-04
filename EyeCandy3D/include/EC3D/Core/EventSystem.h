#pragma once
#include "EC3D/Core/InputObservable.h"
#include "EC3D/Core/DeviceRegistry.h"

#include <memory>

namespace ec
{
	class Window;

	class EventSystem
	{
	public:
		explicit EventSystem(Window* window);
		~EventSystem();

		void dispatchEvent(const InputEvent& event);

		void informAll();

		/** Register a new or remove an old listener */
		void registerInputListener(InputListener* inputListener);
		bool unregisterInputListener(InputListener* inputListener);

		/** Check if this observer contains a specific controller */
		bool contains(InputListener* inputListener);

		/** Clears the input listener list */
		void unregisterAllInputListeners();

		/** 
		 * Check the event queue for new events and inform the
		 * event observable about them.
		 */
		void pollEvents();

		/** 
		 * Get the window from which this event system receives its
		 * events.
		 */
		Window* getWindow() const;

		/** Get the device registry. */
		DeviceRegistry& getDeviceRegistry();

	private:
		Window* m_window;

		DeviceRegistry m_deviceRegistry;
		InputObservable m_inputObservable;
	};
}
