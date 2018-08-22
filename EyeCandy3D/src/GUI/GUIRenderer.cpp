#include "EC3D/Gui/GuiRenderer.h"
#include "EC3D/Gui/GuiSystem.h"
#include "EC3D/Gui/Widget.h"
#include "EC3D/Gui/Gui.h"
#include "EC3D/Gui/Text.h"
#include "EC3D/Gui/Window.h"
#include "EC3D/Gui/Screen.h"

#include "EC3D/Core/Freetype.h"
#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Core/Drawable.h"

#include "EC3D/GUI/GUIModel.h"

#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

namespace ec_gui
{
	void GuiRenderer::render(GuiRenderingParameterList params)
	{
		glEnable(GL_BLEND);
		
		auto guis = m_guiModel->getAllGuIs();
		for(auto& it : guis)
		{
			if(it)
			{
				const auto widget = it->getWidget();
				if(widget)
				{
					GuiRenderingContext context;
					context.m_params = params;
					renderGui(widget, context);
				}
			}
		}	

		glDisable(GL_BLEND);
	}

	void GuiRenderer::render(Text* text, GuiRenderingContext& context)
	{
		glm::vec2 position;
		const glm::mat4& gmat = context.getGlobalMat();

		position.x = gmat[3][0];
		position.y = gmat[3][1];

		auto& params = context.m_params;

		const auto x = position.x - params.m_windowWidth / 2.0f;
		const auto y = params.m_windowHeight / 2.0f + position.y;
		const auto sx = params.m_scaleX;
		const auto sy = params.m_scaleY;

		ec::FontTextureAtlas* atlas = params.m_freetype->getFontTextureAtlas("arial18");
		params.m_freetype->renderText(text->getText().c_str(), atlas, 
									  x * sx, y * sy, 
									  sx, sy,
									  text->getTextColor());
	}

	void GuiRenderer::render(Screen* screen, GuiRenderingContext& context)
	{
		// A screen can't be rendered
	}

	void GuiRenderer::render(Window* window, GuiRenderingContext& context)
	{
		renderCoreElements(window, context);
	}

	void GuiRenderer::renderGui(Widget* widget, GuiRenderingContext& context)
	{
		// Ignore disabled widgets
		if(!widget->isEnabled()) return;

		// Create matrix from the relative position of the current widget
		// Only translation is inherited by child widgets
		const glm::vec2 position = widget->getPosition();
		glm::mat4 relativePos(1);
		relativePos[3][0] = position.x;
		relativePos[3][1] = -position.y;

		// Update global matrix to the one of the current widget and render it
		context.updateGlobalMat(widget);
		widget->render(*this, context);

		// Push matrix of current widget and render its children
		context.save(relativePos);
		auto& children = widget->getChildren();
		for(auto& it : children)
		{
			renderGui(it, context);
		}
		// Pop matrix of current widget
		context.restore();
	}

	void GuiRenderer::renderCoreElements(Widget* widget, GuiRenderingContext& context)
	{
		auto drawable = widget->getDrawable();
		if(drawable)
		{
			drawable->render(context.getGlobalMat());
		}
	}

	void GuiRenderer::render(Widget* widget, GuiRenderingContext& context)
	{
		renderCoreElements(widget, context);
	}

	GuiRenderer::GuiRenderer()
	= default;

	GuiRenderer::~GuiRenderer()
	= default;

	void GuiRenderer::init(GuiModel* guiModel)
	{
		m_guiModel = guiModel;
	}

	ec::Shader* GuiRenderer::getShader() const
	{
		return m_shader;
	}

	void GuiRenderer::setShader(ec::Shader* shader)
	{
		m_shader = shader;
	}

	GuiRenderingContext::GuiRenderingContext()
		: m_globalMat(1)
	{
		m_mats.push(glm::mat4(1));
	}

	GuiRenderingContext::~GuiRenderingContext()
	= default;

	const glm::mat4& GuiRenderingContext::top() const
	{
		return m_mats.top();
	}

	void GuiRenderingContext::save(const glm::mat4& mat)
	{
		m_mats.push(m_mats.top() * mat);
	}

	void GuiRenderingContext::restore()
	{
		m_mats.pop();
	}

	const glm::mat4& GuiRenderingContext::getGlobalMat() const
	{
		return m_globalMat;
	}

	void GuiRenderingContext::updateGlobalMat(Widget* widget)
	{
		glm::vec2 position = widget->getPosition();
		position.x;
		position.y = -position.y;

		glm::mat4 relativePos(1);
		relativePos[3][0] = position.x;
		relativePos[3][1] = position.y;

		
		glm::vec2 size = widget->getSize();
		size *= 0.5f;
		position.x += size.x;
		position.y -= size.y;

		m_globalMat = glm::mat4(1);
		m_globalMat = glm::scale(relativePos, glm::vec3(size, 1));
		m_globalMat[3][0] = position.x;
		m_globalMat[3][1] = position.y;

		m_globalMat = top() * m_globalMat;
	}

}