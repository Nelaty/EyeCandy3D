#include "ec3/Gui/GuiPrimitiveRenderer.h"
#include "ec3/graphics/shader/shader.h"
#include "ec3/graphics/geometry/geometry.h"

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
		float posX = info.m_position.x + info.m_size.x;
		float posY = info.m_position.y - info.m_size.y;


		//posX += info.m_offset.x;
		//posY += info.m_offset.y;
		
		glm::vec2 position(posX + info.m_clippingRect.getX() * 2,
						   posY + info.m_clippingRect.getY() * 2);

		shader->setVec2("uPosition", position);
		shader->setVec2("uScale", info.m_size);
		shader->setVec4("uColor", info.m_color);

		shader->setBool("uIsText", info.m_isText);
		shader->setBool("uHasTexture", info.m_usesTexture);
		if(info.m_usesTexture)
		{
			glActiveTexture(GL_TEXTURE0);
			shader->setInt("material.uTexture", info.m_texture.getId());
			info.m_texture.bind();
		}

		/*m_rectModel = glm::mat4(1);
		m_rectModel = glm::translate(m_rectModel, glm::vec3(rect.getX(), rect.getY(), 0));
		m_rectModel = glm::scale(m_rectModel, glm::vec3(rect.getWidth(), rect.getHeight(), 1));*/
		//m_context.m_guiShader->setMat4("model", m_transform);
	}
}
