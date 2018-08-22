#pragma once
#include "EC3D/Core/InputEvent.h"

namespace ec
{
	class EventQueue
	{
	public:
		explicit EventQueue(unsigned int size = 100);
		~EventQueue();

		void pushEvent(const InputEvent& event);
		bool popEvent(InputEvent& outEvent);

	};
}