#include "EC3D/Core/DynamicGeometry.h"

namespace ec
{
	DynamicGeometry::~DynamicGeometry()
	= default;

	DynamicGeometry::DynamicGeometry()
	= default;

	void DynamicGeometry::beginRender()
	{
		update();
		__super::beginRender();
	}

	void DynamicGeometry::update()
	{
	}
}