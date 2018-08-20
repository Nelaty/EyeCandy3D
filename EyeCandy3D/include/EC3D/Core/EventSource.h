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

		void RegisterEventQueue(EventQueue* queue);
		void UnregisterEventQueue(EventQueue* queue);

		bool ContainsEventQueue(EventQueue* queue);

	private:
		std::vector<EventQueue*> m_eventQueues;
	};
}