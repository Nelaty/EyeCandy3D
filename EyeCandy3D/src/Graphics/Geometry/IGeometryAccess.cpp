#include "ec3/Graphics/Geometry/IGeometryAccess.h"
#include "ec3/Graphics/Shader/Shader.h"

namespace ec
{
	IGeometryAccess::~IGeometryAccess()
	= default;

	void IGeometryAccess::render()
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
