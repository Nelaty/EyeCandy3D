#include "ec3/graphics/geometry/linestrip-geometry.h"

namespace ec
{
	LineStripGeometry::LineStripGeometry()
	{		
	}

	LineStripGeometry::~LineStripGeometry()
	= default;

	void LineStripGeometry::init()
	{
		m_data.releaseMemory();

		const auto vertexCount = m_tempPoints.size();
		if(vertexCount < 2)
		{
			setupMesh();
			return;
		}

		setMode(GL_LINE_STRIP);
		m_data.resizeBuffers(vertexCount, vertexCount);

		auto& vertices = m_data.m_vertices;
		auto& indices = m_data.m_indices;

		for(unsigned int i = 0; i < m_tempPoints.size(); ++i)
		{
			vertices[i].m_position = m_tempPoints[i];
		}
		for(unsigned int i = 0; i < m_tempPoints.size(); ++i)
		{
			indices[i] = i;
		}

		recalculateNormals();
		setupMesh();
	}

	void LineStripGeometry::addVertex(const glm::vec3& vertex)
	{
		m_tempPoints.emplace_back(vertex);
	}

	void LineStripGeometry::setData(glm::vec3* vertices, const int count)
	{
		reset();
		for(int i = 0; i < count; ++i)
		{
			m_tempPoints.emplace_back(vertices[i]);
		}
	}

	void LineStripGeometry::recalculateNormals()
	{
	}

	void LineStripGeometry::reset()
	{
		m_tempPoints.clear();
	}
}
