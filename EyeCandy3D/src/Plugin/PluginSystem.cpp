#include "EC3D/Plugin/PluginSystem.h"
#include "EC3D/Plugin/Plugin.h"
#include "EC3D/Core/Window.h"

#include <algorithm>

namespace ec
{
	PluginSystem::PluginSystem(Window* window)
		: m_window(window)
	{
	}

	PluginSystem::~PluginSystem()
	{
	}

	void PluginSystem::onBegin()
	{
		for(auto& it : m_plugins)
		{
			it->onBegin();
		}
	}

	void PluginSystem::onTick(float timeDelta)
	{
		for(auto& it : m_plugins)
		{
			it->onTick(timeDelta);
		}
	}

	void PluginSystem::onRender(float timeDelta)
	{
		for(auto& it : m_plugins)
		{
			it->onRender(timeDelta);
		}
	}

	void PluginSystem::onEnd()
	{
		for(auto& it : m_plugins)
		{
			it->onEnd();
		}
	}

	void PluginSystem::addPlugin(const Plugin_Ptr& plugin)
	{
		plugin->init(m_window);
		m_plugins.emplace_back(plugin);
	}

	bool PluginSystem::removePlugin(const Plugin_Ptr& plugin)
	{
		auto removedEntry = std::remove(m_plugins.begin(),
										m_plugins.end(),
										plugin);
		if(removedEntry != m_plugins.end())
		{
			(*removedEntry)->cleanup();
			m_plugins.erase(removedEntry);
			return true;
		}
		return false;
	}
}