#include "EC3D/Core/StaticGeometry.h"

namespace ec
{
	StaticGeometry::~StaticGeometry()
	= default;

	StaticGeometry::StaticGeometry()
	= default;

	void StaticGeometry::beginRender()
	{
		glBindVertexArray(m_vao);
	}

	void StaticGeometry::onRender()
	{
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
	}

	void StaticGeometry::endRender()
	{
		glBindVertexArray(0);
	}

	void StaticGeometry::setupMesh()
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_DYNAMIC_COPY);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_DYNAMIC_COPY);


		// positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		// normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, m_normal)));
		// texture coordinates
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, m_texCoords)));

		glBindVertexArray(0);
	}

	void StaticGeometry::recalculateNormals()
	{
		for(auto& it : m_vertices)
		{
			it.m_normal = glm::vec3(0.0f);
		}

		for(size_t i = 0; i < m_indices.size();)
		{
			const auto edge1 = m_vertices[m_indices[i]].m_position - m_vertices[m_indices[i + 1]].m_position;
			const auto edge2 = m_vertices[m_indices[i]].m_position - m_vertices[m_indices[i + 2]].m_position;

			const auto faceNormal = glm::normalize(glm::cross(edge2, edge1));
			m_vertices[m_indices[i]].m_normal += faceNormal;
			m_vertices[m_indices[i + 1]].m_normal += faceNormal;
			m_vertices[m_indices[i + 2]].m_normal += faceNormal;

			i += 3;
		}
		for(auto& it : m_vertices)
		{
			it.m_normal = glm::normalize(it.m_normal);
		}
	}

	GLuint StaticGeometry::getVao() const
	{
		return m_vao;
	}

	GLuint StaticGeometry::getVbo() const
	{
		return m_vbo;
	}

	GLuint StaticGeometry::getEbo() const
	{
		return m_ebo;
	}
}