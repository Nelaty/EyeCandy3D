#include "EC3D/Core/StaticGeometry.h"

namespace ec
{
	StaticGeometry::~StaticGeometry()
	{
	}

	StaticGeometry::StaticGeometry()
	{
	}

	void StaticGeometry::BeginRender()
	{
		glBindVertexArray(m_VAO);
	}

	void StaticGeometry::OnRender()
	{
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	}

	void StaticGeometry::EndRender()
	{
		glBindVertexArray(0);
	}

	void StaticGeometry::SetupMesh()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_DYNAMIC_COPY);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_DYNAMIC_COPY);


		// positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_normal));
		// texture coordinates
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_texCoords));

		glBindVertexArray(0);
	}

	void StaticGeometry::RecalculateNormals()
	{
		for(auto& it : m_vertices)
		{
			it.m_normal = glm::vec3(0.0f);
		}

		for(size_t i = 0; i < m_indices.size();)
		{
			glm::vec3 edge1 = m_vertices[m_indices[i]].m_position - m_vertices[m_indices[i + 1]].m_position;
			glm::vec3 edge2 = m_vertices[m_indices[i]].m_position - m_vertices[m_indices[i + 2]].m_position;

			glm::vec3 faceNormal = glm::normalize(glm::cross(edge2, edge1));
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

	GLuint StaticGeometry::GetVAO() const
	{
		return m_VAO;
	}

	GLuint StaticGeometry::GetVBO() const
	{
		return m_VBO;
	}

	GLuint StaticGeometry::GetEBO() const
	{
		return m_EBO;
	}
}