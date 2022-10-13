#include "ec3/Gui/GuiRenderer.h"
#include "ec3/Window/Window.h"
#include "ec3/Graphics/Text/Freetype.h"

#include "ec3/Graphics/Shader/Shader.h"
#include "ec3/Gui/GuiSystem.h"

#include "Agui/Agui.hpp"

namespace ec
{
	GuiRenderer::GuiRenderer()
	{
	}

	GuiRenderer::~GuiRenderer()
	= default;

	void GuiRenderer::init(Shader* guiShader, Shader* textShader)
	{
		m_freetype = std::make_unique<Freetype>(textShader);

		m_guiRenderContext.m_freetype = m_freetype.get();
		m_guiRenderContext.m_textShader = textShader;
		m_guiRenderContext.m_guiShader = guiShader;
	}

	void GuiRenderer::render(const GuiSystem& guiSystem)
	{
		beginRender(guiSystem);

		guiSystem.render(m_guiRenderContext);

		endRender(guiSystem);
	}

	void GuiRenderer::beginRender(const GuiSystem& guiSystem)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_DEPTH_TEST);

		//glDisable(GL_CULL_FACE); /// \todo: remove -> Testing only
	
	}

	void GuiRenderer::endRender(const GuiSystem& guiSystem)
	{
		glEnable(GL_DEPTH_TEST);

		//glEnable(GL_CULL_FACE); /// \todo: remove -> Testing only
	}


}
