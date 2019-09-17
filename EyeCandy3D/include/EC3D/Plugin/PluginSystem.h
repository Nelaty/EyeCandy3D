#pragma once

#include <memory>
#include <vector>

namespace ec
{
	class Plugin;
	class Window;

	class PluginSystem
	{
	public:
		using Plugin_Ptr = std::shared_ptr<Plugin>;

		explicit PluginSystem(Window* window);
		~PluginSystem();

		void onBegin();
		void onTick(float timeDelta);
		void onRender(float timeDelta);
		void onEnd();

		void addPlugin(const Plugin_Ptr& plugin);
		bool removePlugin(const Plugin_Ptr& plugin);

	private:
		Window* m_window;

		std::vector<Plugin_Ptr> m_plugins;
	};
}