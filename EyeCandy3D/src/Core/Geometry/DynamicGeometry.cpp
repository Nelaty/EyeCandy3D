#include "EC3D/Core/Geometry/DynamicGeometry.h"

namespace ec
{
	DynamicGeometry::~DynamicGeometry()
	= default;

	DynamicGeometry::DynamicGeometry()
	= default;

	void DynamicGeometry::beginRender()
	{
		__super::beginRender();
		update();
	}

	void DynamicGeometry::update()
	{
	}
}