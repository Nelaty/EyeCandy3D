#include "EC3D/Core/IGeometryAccess.h"
#include "EC3D/Core/Shader/Shader.h"

namespace ec
{
	IGeometryAccess::~IGeometryAccess()
	= default;

	void IGeometryAccess::render(Shader* shader, const glm::mat4& model)
	{
		beginRender();
		onRender();
		endRender();
	}

	void IGeometryAccess::beginRender()
	{
	}

	void IGeometryAccess::onRender()
	{
	}

	void IGeometryAccess::endRender()
	{
	}

	IGeometryAccess::IGeometryAccess()
	= default;
}
