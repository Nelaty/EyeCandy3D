#include "EC3D/Core/InputListener.h"

#include <algorithm>

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

	void InputListener::addCallback(const std::string& id, EventKey_T key, std::function<void()> callback)
	{
		const auto cbPair = std::make_pair(id, callback);
		m_eventCallbacks[key].push_back(cbPair);
	}

	bool InputListener::removeCallback(const std::string& id, EventKey_T key)
	{
		auto& cbContainer = m_eventCallbacks[key];
		const auto foundCb = std::remove_if(cbContainer.begin(), cbContainer.end(), 
											[&](const auto& pair) -> bool
		{
			return pair.first == id;
		});

		return foundCb != cbContainer.end();
	}

	void InputListener::removeCallbacksOfType(EventKey_T key)
	{
		auto& cbContainer = m_eventCallbacks[key];
		cbContainer.clear();
	}

	void InputListener::removeAllCallbacks()
	{
		for(auto& it : m_eventCallbacks)
		{
			it.second.clear();
		}
	}

	bool InputListener::isCallbackRegistered(const std::string& id, EventKey_T key)
	{
		auto& cbContainer = m_eventCallbacks[key];
		const auto foundCb = std::find_if(cbContainer.begin(), cbContainer.end(),
									[&](const auto& pair) -> bool
		{
			return pair.first == id;
		});

		return foundCb != cbContainer.end();
	}

	InputListener::InputListener()
		: m_enabled{true}
	{
	}

	void InputListener::processEvent(const InputEvent& event)
	{
		auto& cbContainer = m_eventCallbacks[event.m_type];
		for(const auto& it : cbContainer)
		{
			it.second();
		}
	}

}