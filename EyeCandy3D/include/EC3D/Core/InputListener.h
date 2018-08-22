#pragma once
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
	class InputListener
	{
	public:
		using EventKey_T = InputType;
		using EventCallback_T = std::pair<std::string, std::function<void()>>;
		using EventCallbackContainer_T = std::vector<EventCallback_T>;
		using EventCallbackMap_T = std::map<EventKey_T, EventCallbackContainer_T>;

	public:
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
		void addCallback(const std::string& id, EventKey_T key, std::function<void()> callback);

		/* Remove one specific or multiple callbacks */
		bool removeCallback(const std::string&, EventKey_T key);
		void removeCallbacksOfType(EventKey_T key);
		void removeAllCallbacks();

		/* Check if a certain callback is already registered */
		bool isCallbackRegistered(const std::string& id, EventKey_T key);

	protected:
		explicit InputListener();

		/* Automatically called, when informed about an event */
		virtual void processEvent(const InputEvent& event);

		EventCallbackMap_T m_eventCallbacks;

		bool m_enabled;
	};
}