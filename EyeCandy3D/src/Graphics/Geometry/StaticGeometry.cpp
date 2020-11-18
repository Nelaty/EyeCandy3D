#include "EC3D/Graphics/Geometry/StaticGeometry.h"

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