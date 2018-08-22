#pragma once

#include <vector>

namespace ec
{
	class EventQueue;

	class EventSource
	{
	public:
		explicit EventSource();
		~EventSource();

		void registerEventQueue(EventQueue* queue);
		void unregisterEventQueue(EventQueue* queue);

		bool containsEventQueue(EventQueue* queue);

	private:
		std::vector<EventQueue*> m_eventQueues;
	};
}