#pragma once
#include "ec3/Gui/GuiShaderInfoObject.h"

#include <glm/glm.hpp>

namespace ec
{
	class Shader;
	class Geometry;

	class GuiPrimitiveRenderer
	{
	public:
		explicit GuiPrimitiveRenderer();
		~GuiPrimitiveRenderer();

		void render(Shader* shader,
					const GuiShaderInfoObject& info,
					Geometry* geometry);

	protected:
		static void initShader(Shader* shader,
							   const GuiShaderInfoObject& info);

		glm::mat4 m_transform;
	};	
}
