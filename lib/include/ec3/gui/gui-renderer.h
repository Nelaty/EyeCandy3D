#pragma once
#include "ec3/Graphics/Text/Freetype.h"
#include "ec3/Gui/GuiRenderContext.h"

namespace ec
{
	class Shader;
	class GuiSystem;
	class Window;

	class GuiRenderer
	{
	public:
		explicit GuiRenderer();
		~GuiRenderer();

		void init(Shader* guiShader, Shader* textShader);

		void render(const GuiSystem& guiSystem);

	private:
		void beginRender(const GuiSystem& guiSystem);
		void endRender(const GuiSystem& guiSystem);

		std::unique_ptr<Freetype> m_freetype;
		GuiRenderContext m_guiRenderContext;
	};
}