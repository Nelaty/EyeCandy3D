#include "EC3D/Core/Geometry/IGeometryAccess.h"
#include "EC3D/Core/Shader/Shader.h"

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
