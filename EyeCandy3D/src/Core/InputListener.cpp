#include "EC3D/Core/InputListener.h"

#include <algorithm>

namespace ec
{
	InputListener::~InputListener()
	{
	}

	void InputListener::Inform(const InputEvent& event)
	{
		if(m_enabled)
		{
			ProcessEvent(event);
		}
	}

	void InputListener::Enable(const bool enabled)
	{
		m_enabled = enabled;
	}

	bool InputListener::IsEnabled() const
	{
		return m_enabled;
	}

	void InputListener::AddCallback(const std::string& id, EventKey_T key, std::function<void()> callback)
	{
		auto cbPair = std::make_pair(id, callback);
		m_eventCallbacks[key].push_back(cbPair);
	}

	bool InputListener::RemoveCallback(const std::string& id, EventKey_T key)
	{
		auto& cbContainer = m_eventCallbacks[key];
		auto foundCb = std::remove_if(cbContainer.begin(), cbContainer.end(), 
									  [&](const auto& pair) -> bool
		{
			return pair.first == id;
		});

		return foundCb != cbContainer.end();
	}

	void InputListener::RemoveCallbacksOfType(EventKey_T key)
	{
		auto& cbContainer = m_eventCallbacks[key];
		cbContainer.clear();
	}

	void InputListener::RemoveAllCallbacks()
	{
		for(auto& it : m_eventCallbacks)
		{
			it.second.clear();
		}
	}

	bool InputListener::IsCallbackRegistered(const std::string& id, EventKey_T key)
	{
		auto& cbContainer = m_eventCallbacks[key];
		auto foundCb = std::find_if(cbContainer.begin(), cbContainer.end(),
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

	void InputListener::ProcessEvent(const InputEvent& event)
	{
		auto& cbContainer = m_eventCallbacks[event.m_type];
		for(const auto& it : cbContainer)
		{
			it.second();
		}
	}

}