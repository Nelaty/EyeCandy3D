#include "EC3D/Core/LineGeometry.h"

namespace ec
{
	LineGeometry::LineGeometry(const glm::vec3& start, const glm::vec3& end)
	{
		init(start, end);
	}

	LineGeometry::~LineGeometry()
	= default;

	const glm::vec3& LineGeometry::getStart() const
	{
		return m_start;
	}

	const glm::vec3& LineGeometry::getEnd() const
	{
		return m_end;
	}

	void LineGeometry::recalculateNormals()
	{
		auto& vertices = m_data.m_vertices;
		vertices[0].m_normal = glm::normalize(m_start - m_end);
		vertices[1].m_normal = -vertices[0].m_normal;
	}

	void LineGeometry::init(const glm::vec3& start, const glm::vec3& end)
	{
		setMode(GL_LINES);

		m_start = start;
		m_end = end;

		m_data.resizeBuffers(2, 2);
		auto& vertices = m_data.m_vertices;

		vertices[0].m_position = m_start;
		vertices[1].m_position = m_start;

		vertices[0].m_texCoords = glm::vec2(0.0f, 0.0f);
		vertices[1].m_texCoords = glm::vec2(1.0f, 0.0f);


		auto& indices = m_data.m_indices;
		indices[0] = 0;
		indices[1] = 1;

		recalculateNormals();
		setupMesh();
	}
}


