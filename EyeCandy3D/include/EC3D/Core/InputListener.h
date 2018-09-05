#pragma once
#include "EC3D/Common/Common.h"
#include "InputEvent.h"

#include <vector>
#include <functional>
#include <map>
#include <utility>

/*
* InputListener gets informed about InputEvents from an InputObservable
*/
namespace ec
{
	class EC3D_DECLSPEC InputListener
	{
	public:
		using EventKey_Type = InputType;
		using EventCallback_Type = std::pair<std::string, std::function<void()>>;
		using EventCallbackContainer_Type = std::vector<EventCallback_Type>;
		using EventCallbackMap_Type = std::map<EventKey_Type, EventCallbackContainer_Type>;

		virtual ~InputListener();
		
		/* Inform this controller about an event */
		void inform(const InputEvent& event);

		/* Enable or disable the evaluation of input */
		virtual void enable(bool enabled);
		virtual bool isEnabled() const;

		/* 
		* Add a new callback 
		* Key:	Type of the callback
		* ID:	Identifier of the callback, so it can be retrieved later on
		*		Needs to be unique for an EventType
		*/
		void addCallback(const std::string& id, EventKey_Type key, std::function<void()> callback);

		/* Remove one specific or multiple callbacks */
		bool removeCallback(const std::string&, EventKey_Type key);
		void removeCallbacksOfType(EventKey_Type key);
		void removeAllCallbacks();

		/* Check if a certain callback is already registered */
		bool isCallbackRegistered(const std::string& id, EventKey_Type key);

	protected:
		explicit InputListener();

		/* Automatically called, when informed about an event */
		virtual void processEvent(const InputEvent& event);

		EventCallbackMap_Type m_eventCallbacks;

		bool m_enabled;
	};
}