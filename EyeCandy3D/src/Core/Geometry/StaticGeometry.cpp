#include "EC3D/Core/Geometry/StaticGeometry.h"

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