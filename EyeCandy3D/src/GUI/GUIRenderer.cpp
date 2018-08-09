#include "EC3D/GUI/GUIRenderer.h"
#include "EC3D/GUI/GUISystem.h"
#include "EC3D/GUI/Widget.h"
#include "EC3D/GUI/GUI.h"
#include "EC3D/GUI/Text.h"
#include "EC3D/GUI/Window.h"
#include "EC3D/GUI/Screen.h"

#include "EC3D/Core/Freetype.h"
#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Core/Drawable.h"

#include "EC3D/GUI/GUIModel.h"

#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

namespace ec_gui
{
	GUIRenderer::GUIRenderer()
	{
	}

	GUIRenderer::~GUIRenderer()
	{
	}

	void GUIRenderer::Render(GUIRenderingParameterList params)
	{
		glEnable(GL_BLEND);
		
		auto guis = m_guiModel->GetAllGUIs();
		for(auto& it : guis)
		{
			if(it)
			{
				auto widget = it->GetWidget();
				if(widget)
				{
					GUIRenderingContext context;
					context.m_params = params;
					RenderGUI(widget, context);
				}
			}
		}	

		glDisable(GL_BLEND);
		return;
	}

	void GUIRenderer::Render(Text* text, GUIRenderingContext& context)
	{
		glm::vec2 position;
		const glm::mat4& gmat = context.GetGlobalMat();

		position.x = gmat[3][0];
		position.y = gmat[3][1];

		auto& params = context.m_params;

		float x = position.x -params.m_windowWidth / 2;
		float y = params.m_windowHeight / 2 + position.y;
		float sx = params.m_scaleX;
		float sy = params.m_scaleY;

		ec::FontTextureAtlas* atlas = params.m_freetype->GetFontTextureAtlas("arial18");
		params.m_freetype->RenderText(text->GetText().c_str(), atlas, 
									  x * sx, y * sy, 
									  sx, sy,
									  text->GetTextColor());
	}

	void GUIRenderer::Render(Screen* screen, GUIRenderingContext& context)
	{
		// A screen can't be rendered
	}

	void GUIRenderer::Render(Window* window, GUIRenderingContext& context)
	{
		RenderCoreElements(window, context);
	}

	void GUIRenderer::RenderGUI(Widget* widget, GUIRenderingContext& context)
	{
		// Ignore disabled widgets
		if(!widget->IsEnabled()) return;

		// Create matrix from the relative position of the current widget
		// Only translation is inherited by child widgets
		glm::vec2 position = widget->GetPosition();
		glm::mat4 relativePos(1);
		relativePos[3][0] = position.x;
		relativePos[3][1] = -position.y;

		// Update global matrix to the one of the current widget and render it
		context.UpdateGlobalMat(widget);
		widget->Render(*this, context);

		// Push matrix of current widget and render its children
		context.Save(relativePos);
		auto& children = widget->GetChildren();
		for(auto& it : children)
		{
			RenderGUI(it, context);
		}
		// Pop matrix of current widget
		context.Restore();
	}

	void GUIRenderer::RenderCoreElements(Widget* widget, GUIRenderingContext& context)
	{
		auto drawable = widget->GetDrawable();
		if(drawable)
		{
			drawable->Render(context.GetGlobalMat());
		}
	}

	void GUIRenderer::Render(Widget* widget, GUIRenderingContext& context)
	{
		RenderCoreElements(widget, context);
	}

	void GUIRenderer::Init(GUIModel* guiModel)
	{
		m_guiModel = guiModel;
	}

	ec::Shader* GUIRenderer::GetShader()
	{
		return m_shader;
	}

	void GUIRenderer::SetShader(ec::Shader* shader)
	{
		m_shader = shader;
	}

	GUIRenderingContext::GUIRenderingContext()
		: m_globalMat(1)
	{
		m_mats.push(glm::mat4(1));
	}

	GUIRenderingContext::~GUIRenderingContext()
	{
	}

	const glm::mat4& GUIRenderingContext::Top() const
	{
		return m_mats.top();
	}

	void GUIRenderingContext::Save(const glm::mat4& mat)
	{
		m_mats.push(m_mats.top() * mat);
	}

	void GUIRenderingContext::Restore()
	{
		m_mats.pop();
	}

	const glm::mat4& GUIRenderingContext::GetGlobalMat()
	{
		return m_globalMat;
	}

	void GUIRenderingContext::UpdateGlobalMat(Widget* widget)
	{
		glm::vec2 position = widget->GetPosition();
		position.x;
		position.y = -position.y;

		glm::mat4 relativePos(1);
		relativePos[3][0] = position.x;
		relativePos[3][1] = position.y;

		
		glm::vec2 size = widget->GetSize();
		size *= 0.5f;
		position.x += size.x;
		position.y -= size.y;

		m_globalMat = glm::mat4(1);
		m_globalMat = glm::scale(relativePos, glm::vec3(size, 1));
		m_globalMat[3][0] = position.x;
		m_globalMat[3][1] = position.y;

		m_globalMat = Top() * m_globalMat;
	}

}