#include "EC3D/Core/EventSource.h"
#include "EC3D/Core/EventQueue.h"

namespace ec
{
	EventSource::EventSource()
	= default;

	EventSource::~EventSource()
	= default;

	void EventSource::registerEventQueue(EventQueue* queue)
	{

	}

	void EventSource::unregisterEventQueue(EventQueue* queue)
	{

	}

	bool EventSource::containsEventQueue(EventQueue* queue)
	{
		return false;
	}

}