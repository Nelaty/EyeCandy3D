#pragma once
#include "ec3/common/common.h"
#include "ec3/input/input-event.h"

#include <vector>
#include <functional>
#include <utility>
#include <array>

/**
* \brief InputListener gets informed about InputEvents from an InputObservable
*/
namespace ec
{
	/**
	 * \brief An InputListener can react on incoming events.
	 * It can either be used as a base class or be filled with callbacks.
	 */
	class EC3D_DECLSPEC InputListener
	{
	public:
		using EventKey_Type = InputType;
		using EventCallback_Type = std::function<void(const InputEvent& event)>;
		using EventCallbackContainer_Type = std::vector<EventCallback_Type>;
		using CallbackContainerMap_Type = std::array<EventCallbackContainer_Type, static_cast<int>(InputType::count)>;


		virtual ~InputListener();
		
		/**
		 * \brief Inform this controller about an event.
		 * \param event The event to process.
		 */
		void inform(const InputEvent& event);

		/**
		 * \brief Enable or disable the evaluation of input.
		 * \param enabled If true incoming events will be 
		 * processed.
		 */
		virtual void enable(bool enabled);
		/**
		 * \brief Check if this input listener is processing events.
		 */
		virtual bool isEnabled() const;

		/* 
		* \brief Add a new callback.
		* \param key Type of the callback.
		* \param callback The new callback.
		*/
		void addCallback(EventKey_Type key,
						 EventCallback_Type callback);

		/**
		 * \brief Remove one specific or multiple callbacks.
		 * \param key The type of the callbacks to remove. 
		 */
		void removeCallbacksOfType(EventKey_Type key);
		/**
		 * \brief Remove all registered callbacks.
		 */
		void removeAllCallbacks();

	protected:
		explicit InputListener();

		/**
		 * \brief Automatically called, when informed about an event.
		 */
		virtual void processEvent(const InputEvent& event);

		CallbackContainerMap_Type m_callbackContainers;

		bool m_enabled;
	};
}