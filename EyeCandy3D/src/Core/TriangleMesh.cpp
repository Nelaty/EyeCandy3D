#include "EC3D/Core/TriangleMesh.h"

namespace ec
{
	
	TriangleMesh::TriangleMesh()
	{
	}

	TriangleMesh::TriangleMesh(const GeometryData& data)
	{
		m_data = data;
		init();
	}

	TriangleMesh::~TriangleMesh()
	{
	}

	void TriangleMesh::setData(const GeometryData& data)
	{
		m_data = data;
		init();

	}

	void TriangleMesh::init()
	{
		setupMesh();
	}

}