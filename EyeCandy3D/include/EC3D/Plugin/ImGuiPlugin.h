#pragma once
#include "Plugin.h"

namespace ec
{
	class ImGuiPlugin : public Plugin
	{
	public:
		explicit ImGuiPlugin();
		~ImGuiPlugin();

		void init(Window* window) override;

		void onBegin() override;
		void onTick(float timeDelta) override;
		void onRender(float timeDelta) override;
		void onEnd() override;

		void cleanup() override;

	private:
		Window* m_window;
	};
}