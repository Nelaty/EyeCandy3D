#pragma once

namespace ec
{
	class Window;

	class Plugin
	{
	public:
		virtual ~Plugin() = 0;

		virtual void init(Window* window);

		virtual void onBegin();
		virtual void onTick(float timeDelta);
		virtual void onRender(float timeDelta);
		virtual void onEnd();

		virtual void cleanup();

	protected:
		explicit Plugin();
	};
}