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

	void InputListener::addCallback(const std::string& id, 
									EventKey_Type key, 
									std::function<void()> callback)
	{
		const auto cbPair = std::make_pair(id, callback);
		m_callbackContainers[static_cast<int>(key)].emplace_back(EventCallback_Type(id, callback));
	}

	bool InputListener::removeCallback(const std::string& id, EventKey_Type key)
	{
		auto& cbContainer = m_callbackContainers[static_cast<int>(key)];
		const auto foundCb = std::remove_if(cbContainer.begin(), cbContainer.end(), 
											[&](const auto& pair) -> bool
		{
			return pair.first == id;
		});

		return foundCb != cbContainer.end();
	}

	void InputListener::removeCallbacksOfType(EventKey_Type key)
	{
		auto& cbContainer = m_callbackContainers[static_cast<int>(key)];
		cbContainer.clear();
	}

	void InputListener::removeAllCallbacks()
	{
		for(auto& it : m_callbackContainers)
		{
			it.clear();
		}
	}

	bool InputListener::isCallbackRegistered(const std::string& id, EventKey_Type key)
	{
		auto& cbContainer = m_callbackContainers[static_cast<int>(key)];
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
		auto& cbContainer = m_callbackContainers[static_cast<int>(event.m_type)];
		for(const auto& it : cbContainer)
		{
			it.second();
		}
	}

}