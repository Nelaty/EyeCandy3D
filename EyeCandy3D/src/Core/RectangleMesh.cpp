#include "EC3D/Core/RectangleMesh.h"
#include "EC3D/Core/Shader/Shader.h"

#include <gl/glew.h>

namespace ec
{


	RectangleMesh::RectangleMesh(const float uniform /*= 1.0f*/)
	{
		Init(uniform, uniform);
		SetupMesh();
	}

	RectangleMesh::RectangleMesh(const float width, const float height)
	{
		Init(width, height);
	}

	RectangleMesh::~RectangleMesh()
	{
	}

	void RectangleMesh::Init(const float width, const float height)
	{
		m_vertices.resize(4);
		m_indices.resize(6);

		float halfWidth = width;
		float halfHeight = height;

		// Initialize vertices
		// 0,0---0,1
		// |      |
		// 1,0---1,1
		m_vertices[0].m_position = glm::vec3(-halfWidth, -halfHeight, 0.0f);
		m_vertices[0].m_normal = glm::vec3(0.0f, 0.0f, 1.0f);
		m_vertices[0].m_texCoords = glm::vec2(1.0f, 1.0f);

		m_vertices[1].m_position = glm::vec3(halfWidth, -halfHeight, 0.0f);
		m_vertices[1].m_normal = glm::vec3(0.0f, 0.0f, 1.0f);
		m_vertices[1].m_texCoords = glm::vec2(0.0f, 1.0f);

		m_vertices[2].m_position = glm::vec3(halfWidth, halfHeight, 0.0f);
		m_vertices[2].m_normal = glm::vec3(0.0f, 0.0f, 1.0f);
		m_vertices[2].m_texCoords = glm::vec2(0.0f, 0.0f);

		m_vertices[3].m_position = glm::vec3(-halfWidth, halfHeight, 0.0f);
		m_vertices[3].m_normal = glm::vec3(0.0f, 0.0f, 1.0f);
		m_vertices[3].m_texCoords = glm::vec2(1.0f, 0.0f);

		// Initialize index list
		m_indices.push_back(0);
		m_indices.push_back(1);
		m_indices.push_back(2);

		m_indices.push_back(2);
		m_indices.push_back(3);
		m_indices.push_back(0);
	}
}