#include "ec3/graphics/geometry/static-geometry.h"

namespace ec
{
	StaticGeometry::~StaticGeometry()
	= default;

	StaticGeometry::StaticGeometry()
	= default;

	void StaticGeometry::setupMesh()
	{
		m_data.initBufferObjects();
	}
}