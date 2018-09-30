#pragma once
#include "EC3D/Core/Freetype.h"
#include "EC3D/Gui/GuiRenderContext.h"

namespace ec
{
	class Shader;
	class GuiSystem;
	class Window;

	class GuiRenderer
	{
	public:
		explicit GuiRenderer(Window* window);
		~GuiRenderer();

		void init(Shader* guiShader, Shader* textShader);

		void render(const GuiSystem& guiSystem);

	private:
		void beginRender(const GuiSystem& guiSystem);
		void endRender(const GuiSystem& guiSystem);

		Window* m_window;

		std::unique_ptr<Freetype> m_freetype;
		GuiRenderContext m_guiRenderContext;
	};
}