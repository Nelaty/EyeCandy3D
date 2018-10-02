#include "EC3D/Gui/GuiPrimitiveRenderer.h"
#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Core/Geometry.h"

namespace ec
{
	GuiPrimitiveRenderer::GuiPrimitiveRenderer()
	= default;

	GuiPrimitiveRenderer::~GuiPrimitiveRenderer()
	= default;

	void GuiPrimitiveRenderer::render(Shader* shader,
									  const GuiShaderInfoObject& info, 
									  Geometry* geometry)
	{
		initShader(shader, info);
		geometry->render();
	}

	void GuiPrimitiveRenderer::initShader(Shader* shader, 
										  const GuiShaderInfoObject& info)
	{
		glm::vec2 position(info.m_position.x + info.m_size.x + info.m_clippingRect.getX() * 2,
						   info.m_position.y + -info.m_size.y + info.m_clippingRect.getY() * 2);

		shader->setVec2("uPosition", position);
		shader->setVec2("uScale", info.m_size);
		shader->setVec4("uColor", info.m_color);

		shader->setBool("uHasTexture", info.m_usesTexture);
		if(info.m_usesTexture)
		{
			
		}

		/*m_rectModel = glm::mat4(1);
		m_rectModel = glm::translate(m_rectModel, glm::vec3(rect.getX(), rect.getY(), 0));
		m_rectModel = glm::scale(m_rectModel, glm::vec3(rect.getWidth(), rect.getHeight(), 1));*/
		//m_context.m_guiShader->setMat4("model", m_transform);
	}
}
