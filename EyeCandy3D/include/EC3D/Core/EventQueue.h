#pragma once
#include "EC3D/Core/InputEvent.h"

namespace ec
{
	class EventQueue
	{
	public:
		explicit EventQueue(unsigned int size = 100);
		~EventQueue();

		void PushEvent(const InputEvent& event);
		bool PopEvent(InputEvent& outEvent);

	private:

	};
}