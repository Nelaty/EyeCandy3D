#include "EC3D/Core/Geometry.h"
#include "EC3D/Core/Shader/Shader.h"

namespace ec
{
	Geometry::~Geometry()
	= default;

	void Geometry::render(Shader* shader, const glm::mat4& model)
	{
		beginRender();
		onRender();
		endRender();
	}

	void Geometry::beginRender()
	{
	}

	void Geometry::onRender()
	{
	}

	void Geometry::endRender()
	{
	}
}