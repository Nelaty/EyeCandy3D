#include "EC3D/Core/Input/EventProcessor.h"
#include "EC3D/Core/Input/InputListener.h"

#include <algorithm>

namespace ec
{
	EventProcessor::EventProcessor()
	{
	}

	EventProcessor::~EventProcessor()
	{
	}

	void EventProcessor::receiveEvent(const InputEvent& event)
	{
		for(auto& it : m_inputListeners)
		{
			it->inform(event);
		}
	}

	void EventProcessor::registerInputListener(InputListener* inputListener)
	{
		m_inputListeners.emplace_back(inputListener);
	}

	bool EventProcessor::unregisterInputListener(InputListener* inputListener)
	{
		const auto removedItem = std::remove(m_inputListeners.begin(),
											 m_inputListeners.end(),
											 inputListener);

		return removedItem != m_inputListeners.end();
	}

	bool EventProcessor::contains(InputListener* inputListener)
	{
		const auto foundItem = std::find(m_inputListeners.begin(),
										 m_inputListeners.end(),
										 inputListener);

		return foundItem != m_inputListeners.end();
	}

	void EventProcessor::unregisterAllInputListeners()
	{
		m_inputListeners.clear();
	}

}