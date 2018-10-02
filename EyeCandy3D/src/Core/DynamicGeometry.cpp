#include "EC3D/Core/DynamicGeometry.h"

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