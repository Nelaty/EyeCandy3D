#include "ec3/Input/InputListener.h"

namespace ec
{
	InputListener::~InputListener()
	= default;

	void InputListener::inform(const InputEvent& event)
	{
		if(m_enabled)
		{
			processEvent(event);
		}
	}

	void InputListener::enable(const bool enabled)
	{
		m_enabled = enabled;
	}

	bool InputListener::isEnabled() const
	{
		return m_enabled;
	}

	void InputListener::addCallback(EventKey_Type key, 
									EventCallback_Type callback)
	{
		m_callbackContainers[int(key)].emplace_back(callback);
	}

	void InputListener::removeCallbacksOfType(EventKey_Type key)
	{
		auto& cbContainer = m_callbackContainers[int(key)];
		cbContainer.clear();
	}

	void InputListener::removeAllCallbacks()
	{
		for(auto& it : m_callbackContainers)
		{
			it.clear();
		}
	}

	InputListener::InputListener()
		: m_enabled{true}
	{
	}

	void InputListener::processEvent(const InputEvent& event)
	{
		auto& cbContainer = m_callbackContainers[int(event.m_type)];
		for(auto& it : cbContainer)
		{
			it(event);
		}
	}

}