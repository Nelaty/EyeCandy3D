#include "EC3D/Graphics/Geometry/IGeometryAccess.h"
#include "EC3D/Graphics/Shader/Shader.h"

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
