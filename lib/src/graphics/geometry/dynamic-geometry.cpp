#include "ec3/graphics/geometry/dynamic-geometry.h"

namespace ec
{
	DynamicGeometry::~DynamicGeometry()
	= default;

	DynamicGeometry::DynamicGeometry()
	= default;

	void DynamicGeometry::beginRender()
	{
		Geometry::beginRender();
		update();
	}

	void DynamicGeometry::update()
	{
	}
}
