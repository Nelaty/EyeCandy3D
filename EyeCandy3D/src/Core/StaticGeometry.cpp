#include "EC3D/Core/StaticGeometry.h"

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