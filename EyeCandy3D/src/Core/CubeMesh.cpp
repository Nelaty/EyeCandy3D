#include "EC3D/Core/CubeMesh.h"

#include <array>

namespace ec
{
	CubeMesh::CubeMesh(const float uniformSize)
	{
		Init(uniformSize, uniformSize, uniformSize);
	}

	CubeMesh::CubeMesh(const float width, const float height, const float depth)
	{
		Init(width, height, depth);
	}

	CubeMesh::~CubeMesh()
	{
	}
	
	void CubeMesh::Resize(float width, float height, float depth)
	{
		Init(width, height, depth);
	}

	void CubeMesh::Init(const float width, const float height, const float depth)
	{
		m_vertices = std::vector<Vertex>(8);
		m_indices = std::vector<unsigned int>(36);
		glm::vec3 halfSizes(0.5f * width, 0.5f * height, 0.5f * depth);

		// Vertex positions
		m_vertices[0].m_position = glm::vec3(-halfSizes.x, -halfSizes.y, halfSizes.z);
		m_vertices[1].m_position = glm::vec3(halfSizes.x, -halfSizes.y, halfSizes.z);
		m_vertices[2].m_position = glm::vec3(halfSizes.x, halfSizes.y, halfSizes.z);
		m_vertices[3].m_position = glm::vec3(-halfSizes.x, halfSizes.y, halfSizes.z);

		m_vertices[4].m_position = glm::vec3(-halfSizes.x, -halfSizes.y, -halfSizes.z);
		m_vertices[5].m_position = glm::vec3(halfSizes.x, -halfSizes.y, -halfSizes.z);
		m_vertices[6].m_position = glm::vec3(halfSizes.x, halfSizes.y, -halfSizes.z);
		m_vertices[7].m_position = glm::vec3(-halfSizes.x, halfSizes.y, -halfSizes.z);

		// Vertex texture coordinates
		m_vertices[0].m_texCoords = glm::vec2(0.0f, 0.0f);
		m_vertices[1].m_texCoords = glm::vec2(1.0f, 0.0f);
		m_vertices[2].m_texCoords = glm::vec2(1.0f, 1.0f);
		m_vertices[3].m_texCoords = glm::vec2(0.0f, 1.0f);

		m_vertices[4].m_texCoords = glm::vec2(1.0f, 1.0f);
		m_vertices[5].m_texCoords = glm::vec2(0.0f, 1.0f);
		m_vertices[6].m_texCoords = glm::vec2(0.0f, 0.0f);
		m_vertices[7].m_texCoords = glm::vec2(1.0f, 0.0f);

		// Front
		m_indices[0] = 0;
		m_indices[1] = 1;
		m_indices[2] = 2;
		m_indices[3] = 0;
		m_indices[4] = 2;
		m_indices[5] = 3;

		// Left
		m_indices[6] = 4;
		m_indices[7] = 0;
		m_indices[8] = 3;
		m_indices[9] = 4;
		m_indices[10] = 3;
		m_indices[11] = 7;


		// Right
		m_indices[12] = 1;
		m_indices[13] = 5;
		m_indices[14] = 6;
		m_indices[15] = 1;
		m_indices[16] = 6;
		m_indices[17] = 2;

		// Top
		m_indices[18] = 3;
		m_indices[19] = 2;
		m_indices[20] = 6;
		m_indices[21] = 3;
		m_indices[22] = 6;
		m_indices[23] = 7;

		// Bottom
		m_indices[24] = 4;
		m_indices[25] = 5;
		m_indices[26] = 1;
		m_indices[27] = 4;
		m_indices[28] = 1;
		m_indices[29] = 0;

		// Back
		m_indices[30] = 5;
		m_indices[31] = 4;
		m_indices[32] = 7;
		m_indices[33] = 5;
		m_indices[34] = 7;
		m_indices[35] = 6;

		RecalculateNormals();
		SetupMesh();
	}
}