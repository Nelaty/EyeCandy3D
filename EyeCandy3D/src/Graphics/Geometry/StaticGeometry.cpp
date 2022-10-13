#include "ec3/Graphics/Geometry/StaticGeometry.h"

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