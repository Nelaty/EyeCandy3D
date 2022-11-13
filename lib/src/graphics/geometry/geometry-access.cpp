#include "ec3/graphics/geometry/geometry-access.h"

#include "ec3/graphics/shader/shader.h"

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
